#include "rfid_module.h"
#include "hardware_pinout.h"
#include <SPI.h>

RFIDModule rfidModule;

// Minimal MFRC522 register ops (software SPI if needed, but use HW SPI)
#define MFRC522_REG_COMMAND     0x01
#define MFRC522_REG_COMIEN      0x02
#define MFRC522_REG_DIVIEN      0x03
#define MFRC522_REG_COMIRQ      0x04
#define MFRC522_REG_ERROR       0x06
#define MFRC522_REG_STATUS2     0x08
#define MFRC522_REG_FIFO_DATA   0x09
#define MFRC522_REG_FIFO_LEVEL  0x0A
#define MFRC522_REG_CONTROL     0x0C
#define MFRC522_REG_BIT_FRAMING 0x0D
#define MFRC522_REG_MODE        0x11
#define MFRC522_REG_TX_CONTROL  0x14
#define MFRC522_REG_TX_ASK      0x15
#define MFRC522_REG_CRC_RESULT_H 0x21
#define MFRC522_REG_CRC_RESULT_L 0x22
#define MFRC522_REG_VERSION     0x37

#define PCD_IDLE                0x00
#define PCD_TRANSCEIVE          0x0C
#define PCD_SOFTRESET           0x0F
#define PICC_CMD_REQA           0x26
#define PICC_CMD_WUPA           0x52
#define PICC_CMD_SEL_CL1        0x93
#define PICC_CMD_HLTA           0x50

static void mfrc522_write(uint8_t reg, uint8_t val) {
    if (RFID_CS < 0) return;
    digitalWrite(RFID_CS, LOW);
    SPI.transfer((reg << 1) & 0x7E);
    SPI.transfer(val);
    digitalWrite(RFID_CS, HIGH);
}

static uint8_t mfrc522_read(uint8_t reg) {
    if (RFID_CS < 0) return 0;
    digitalWrite(RFID_CS, LOW);
    SPI.transfer(((reg << 1) & 0x7E) | 0x80);
    uint8_t v = SPI.transfer(0);
    digitalWrite(RFID_CS, HIGH);
    return v;
}

static void mfrc522_setBitMask(uint8_t reg, uint8_t mask) {
    mfrc522_write(reg, mfrc522_read(reg) | mask);
}

static void mfrc522_clearBitMask(uint8_t reg, uint8_t mask) {
    mfrc522_write(reg, mfrc522_read(reg) & (~mask));
}

static void mfrc522_antennaOn() {
    uint8_t v = mfrc522_read(MFRC522_REG_TX_CONTROL);
    if (!(v & 0x03)) {
        mfrc522_setBitMask(MFRC522_REG_TX_CONTROL, 0x03);
    }
}

static bool mfrc522_toCard(uint8_t command, uint8_t *sendData, uint8_t sendLen,
                           uint8_t *backData, uint8_t *backLen) {
    uint8_t irqEn = 0x00, waitIRq = 0x00;
    if (command == PCD_TRANSCEIVE) {
        irqEn = 0x77;
        waitIRq = 0x30;
    }
    mfrc522_write(MFRC522_REG_COMIEN, irqEn | 0x80);
    mfrc522_clearBitMask(MFRC522_REG_COMIRQ, 0x80);
    mfrc522_setBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
    mfrc522_write(MFRC522_REG_COMMAND, PCD_IDLE);

    for (uint8_t i = 0; i < sendLen; i++) {
        mfrc522_write(MFRC522_REG_FIFO_DATA, sendData[i]);
    }
    mfrc522_write(MFRC522_REG_COMMAND, command);
    if (command == PCD_TRANSCEIVE) {
        mfrc522_setBitMask(MFRC522_REG_BIT_FRAMING, 0x80);
    }

    uint16_t i = 2000;
    uint8_t n;
    do {
        n = mfrc522_read(MFRC522_REG_COMIRQ);
        i--;
    } while (i && !(n & 0x01) && !(n & waitIRq));

    mfrc522_clearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);
    if (i == 0) return false;
    if (mfrc522_read(MFRC522_REG_ERROR) & 0x1B) return false;

    if (command == PCD_TRANSCEIVE) {
        n = mfrc522_read(MFRC522_REG_FIFO_LEVEL);
        uint8_t lastBits = mfrc522_read(MFRC522_REG_CONTROL) & 0x07;
        if (lastBits) *backLen = (n - 1) * 8 + lastBits;
        else *backLen = n * 8;
        if (n == 0) n = 1;
        if (n > 16) n = 16;
        for (uint8_t j = 0; j < n; j++) {
            backData[j] = mfrc522_read(MFRC522_REG_FIFO_DATA);
        }
    }
    return true;
}

void RFIDModule::begin() {
    if (initialized) return;
    if (RFID_CS < 0 || RFID_RST < 0) {
        logger.log(LOG_WARN, "RFID", "RFID pins disabled (enable via Module Control)");
        return;
    }
    pinMode(RFID_CS, OUTPUT);
    pinMode(RFID_RST, OUTPUT);
    digitalWrite(RFID_CS, HIGH);
    digitalWrite(RFID_RST, LOW);
    delay(50);
    digitalWrite(RFID_RST, HIGH);
    delay(50);

    SPI.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, RFID_CS);

    mfrc522_write(MFRC522_REG_COMMAND, PCD_SOFTRESET);
    delay(50);
    mfrc522_write(0x12, 0x00); // TxModeReg
    mfrc522_write(0x13, 0x00); // RxModeReg
    mfrc522_write(MFRC522_REG_MODE, 0x3D);
    mfrc522_write(MFRC522_REG_TX_ASK, 0x40);
    mfrc522_antennaOn();

    uint8_t ver = mfrc522_read(MFRC522_REG_VERSION);
    logger.log(LOG_INFO, "RFID", ("MFRC522 version: 0x" + String(ver, HEX)).c_str());
    initialized = (ver == 0x91 || ver == 0x92 || ver == 0x12);
    if (!initialized) {
        logger.log(LOG_WARN, "RFID", "MFRC522 not detected");
    } else {
        logger.log(LOG_INFO, "RFID", "MFRC522 ready");
    }
    savedCount = 0;
}

void RFIDModule::init() { begin(); }

void RFIDModule::end() {
    if (RFID_CS >= 0) digitalWrite(RFID_CS, HIGH);
    initialized = false;
}

bool RFIDModule::readCard() {
    if (!initialized) return false;

    uint8_t bufferATQA[2];
    uint8_t bufferSize = sizeof(bufferATQA);
    uint8_t cmd[1] = { PICC_CMD_REQA };
    // REQA is 7-bit, need bit framing
    mfrc522_write(MFRC522_REG_BIT_FRAMING, 0x07);
    if (!mfrc522_toCard(PCD_TRANSCEIVE, cmd, 1, bufferATQA, &bufferSize)) {
        return false;
    }
    mfrc522_write(MFRC522_REG_BIT_FRAMING, 0x00);

    // Anticollision CL1
    uint8_t serNum[5];
    uint8_t serNumCheck = 0;
    bufferSize = 5;
    uint8_t cmd2[2] = { PICC_CMD_SEL_CL1, 0x20 };
    if (!mfrc522_toCard(PCD_TRANSCEIVE, cmd2, 2, serNum, &bufferSize)) {
        return false;
    }
    for (uint8_t i = 0; i < 4; i++) {
        serNumCheck ^= serNum[i];
    }
    if (serNumCheck != serNum[4]) return false;

    lastCard.uidLen = 4;
    lastCard.uidStr = "";
    for (int i = 0; i < 4; i++) {
        lastCard.uid[i] = serNum[i];
        char hex[4];
        snprintf(hex, sizeof(hex), "%02X", serNum[i]);
        lastCard.uidStr += hex;
        if (i < 3) lastCard.uidStr += ":";
    }
    logger.logCapture("RFID", ("UID: " + lastCard.uidStr).c_str());
    buzzer.success();
    return true;
}

void RFIDModule::saveCard() {
    if (savedCount < 20 && lastCard.uidLen > 0) {
        savedCards[savedCount] = lastCard;
        savedCount++;
        buzzer.success();
        logger.log(LOG_INFO, "RFID", ("Saved UID " + lastCard.uidStr).c_str());
    }
}

int RFIDModule::getSavedCount() { return savedCount; }
RFIDTag* RFIDModule::getSavedCards() { return savedCards; }
RFIDTag RFIDModule::getLastCard() { return lastCard; }
void RFIDModule::clearSaved() { savedCount = 0; }
