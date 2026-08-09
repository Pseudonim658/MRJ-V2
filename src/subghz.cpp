#include "subghz.h"

SubGHzModule subGHz;

void SubGHzModule::init() {
    begin();
}

void SubGHzModule::begin() {
    if (initialized) return;
    if (CC1101_CS < 0) {
        logger.log(LOG_WARN, "SUBGHZ", "CC1101 disabled (CS pin -1)");
        return;
    }
    pinMode(CC1101_CS, OUTPUT);
    digitalWrite(CC1101_CS, HIGH);
    SPI.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, CC1101_CS);
    digitalWrite(CC1101_CS, LOW);
    delayMicroseconds(10);
    digitalWrite(CC1101_CS, HIGH);
    delayMicroseconds(40);
    cc1101_strobe(0x30);
    delay(10);
    setFrequency(SUBGHZ_DEFAULT_FREQ);
    initialized = true;
    logger.log(LOG_INFO, "SUBGHZ", "CC1101 initialized (shared CS)");
}

void SubGHzModule::end() {
    initialized = false;
    digitalWrite(CC1101_CS, HIGH);
    pinMode(CC1101_CS, INPUT);  // Release shared CS pin
    if (CC1101_GDO0 >= 0) pinMode(CC1101_GDO0, INPUT);
    logger.log(LOG_INFO, "SUBGHZ", "CC1101 ended, pins released");
}

void SubGHzModule::cc1101_write(uint8_t addr, uint8_t data) {
    if (CC1101_CS < 0) return;
    digitalWrite(CC1101_CS, LOW);
    SPI.transfer(addr);
    SPI.transfer(data);
    digitalWrite(CC1101_CS, HIGH);
}

uint8_t SubGHzModule::cc1101_read(uint8_t addr) {
    if (CC1101_CS < 0) return 0;
    digitalWrite(CC1101_CS, LOW);
    SPI.transfer(addr | 0x80);
    uint8_t val = SPI.transfer(0);
    digitalWrite(CC1101_CS, HIGH);
    return val;
}

void SubGHzModule::cc1101_strobe(uint8_t strobe) {
    if (CC1101_CS < 0) return;
    digitalWrite(CC1101_CS, LOW);
    SPI.transfer(strobe);
    digitalWrite(CC1101_CS, HIGH);
}

void SubGHzModule::setFrequency(float freq) {
    frequency = freq;
    uint32_t freqReg = (uint32_t)(freq * 65536.0f / 26.0f);
    cc1101_write(0x0D, (freqReg >> 16) & 0xFF);
    cc1101_write(0x0E, (freqReg >> 8) & 0xFF);
    cc1101_write(0x0F, freqReg & 0xFF);
}

float SubGHzModule::getFrequency() { return frequency; }

void SubGHzModule::startReceive() {
    if (!initialized) return;
    cc1101_strobe(0x34);
    receiving = true;
    dataReady = false;
    logger.log(LOG_INFO, "SUBGHZ", ("RX on " + String(frequency, 2) + " MHz").c_str());
}

void SubGHzModule::stopReceive() {
    if (!initialized) return;
    cc1101_strobe(0x36);
    receiving = false;
}

void SubGHzModule::sendData(uint8_t* data, uint8_t len) {
    if (!initialized) return;
    cc1101_strobe(0x36);
    cc1101_strobe(0x3B);
    digitalWrite(CC1101_CS, LOW);
    SPI.transfer(0x7F);
    SPI.transfer(len);
    for (int i = 0; i < len; i++) {
        SPI.transfer(data[i]);
    }
    digitalWrite(CC1101_CS, HIGH);
    cc1101_strobe(0x35);
    delay(50);
    cc1101_strobe(0x36);
    logger.log(LOG_INFO, "SUBGHZ", ("Sent " + String(len) + " bytes").c_str());
    buzzer.success();
}

void SubGHzModule::sendLast() {
    if (lastDataLen > 0) {
        sendData(lastData, lastDataLen);
    }
}

void SubGHzModule::freqScan() {
    if (!initialized) return;
    logger.log(LOG_INFO, "SUBGHZ", "Freq scan 300-928MHz started");
    for (float f = SUBGHZ_MIN_FREQ; f <= SUBGHZ_MAX_FREQ; f += 1.0f) {
        setFrequency(f);
        cc1101_strobe(0x34);
        delayMicroseconds(500);
        uint8_t rssi = cc1101_read(0x34);
        if (rssi > 100) {
            Serial.printf("[SUBGHZ] Signal at %.2f MHz, RSSI: %d\n", f, rssi);
        }
        cc1101_strobe(0x36);
    }
    setFrequency(frequency);
}

bool SubGHzModule::isReceiving() { return receiving; }
bool SubGHzModule::hasData() { return dataReady; }
uint8_t* SubGHzModule::getLastData() { return lastData; }
uint8_t SubGHzModule::getLastDataLen() { return lastDataLen; }

void SubGHzModule::update() {
    if (!initialized || !receiving) return;
    uint8_t status = cc1101_read(0x3B);
    if (status & 0x7F) {
        lastDataLen = cc1101_read(0xFF);
        if (lastDataLen > 0 && lastDataLen <= 64) {
            digitalWrite(CC1101_CS, LOW);
            SPI.transfer(0xFF);
            for (int i = 0; i < lastDataLen; i++) {
                lastData[i] = SPI.transfer(0);
            }
            digitalWrite(CC1101_CS, HIGH);
            dataReady = true;
            buzzer.beep(3000, 50);
            logger.logCapture("SUBGHZ", ("Received " + String(lastDataLen) + " bytes").c_str());
            if (savedCount < 10) {
                memcpy(savedSignals[savedCount], lastData, lastDataLen);
                savedLens[savedCount] = lastDataLen;
                savedCount++;
            }
            cc1101_strobe(0x3A);
            cc1101_strobe(0x34);
        }
    }
}
