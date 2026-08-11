#include "ir_remote.h"
#include "eeprom_manager.h"

IRRemoteModule irRemote;

void IRRemoteModule::init() {
    pinMode(IR_RECV_PIN, INPUT);
    pinMode(IR_SEND_PIN, OUTPUT);
    digitalWrite(IR_SEND_PIN, LOW);
    savedCount = 0;
    recording = false;
    txEnabled = eeprom.isModuleEnabled(EE_MODULE_IR_SEND);
    logger.log(LOG_INFO, "IR", "IR Remote initialized");
}

void IRRemoteModule::enableTx() {
    txEnabled = true;
    pinMode(IR_SEND_PIN, OUTPUT);
    digitalWrite(IR_SEND_PIN, LOW);
}

void IRRemoteModule::disableTx() {
    txEnabled = false;
    pinMode(IR_SEND_PIN, INPUT);
}

void IRRemoteModule::startRecord() {
    recording = true;
    pulseIdx = 0;
    lastPulse = micros();
    lastSignal.rawLen = 0;
    logger.log(LOG_INFO, "IR", "Recording started");
    buzzer.click();
}

void IRRemoteModule::stopRecord() {
    recording = false;
    lastSignal.rawLen = pulseIdx;
    if (pulseIdx > 0) {
        logger.log(LOG_INFO, "IR", ("Recorded " + String(pulseIdx) + " pulses").c_str());
        buzzer.success();
    }
}

bool IRRemoteModule::isRecording() { return recording; }
bool IRRemoteModule::hasSignal() { return lastSignal.rawLen > 0; }

void IRRemoteModule::playSignal(int idx) {
    if (!txEnabled) {
        logger.log(LOG_WARN, "IR", "IR TX disabled");
        return;
    }
    IRSignal* sig = (idx >= 0 && idx < savedCount) ? &savedSignals[idx] : &lastSignal;
    if (sig->rawLen == 0) return;

    for (int i = 0; i < sig->rawLen; i++) {
        if (i % 2 == 0) {
            unsigned long start = micros();
            while (micros() - start < sig->rawData[i]) {
                digitalWrite(IR_SEND_PIN, HIGH);
                delayMicroseconds(13);
                digitalWrite(IR_SEND_PIN, LOW);
                delayMicroseconds(13);
            }
        } else {
            delayMicroseconds(sig->rawData[i]);
        }
    }
    digitalWrite(IR_SEND_PIN, LOW);
    logger.log(LOG_INFO, "IR", "Signal played");
    buzzer.click();
}

void IRRemoteModule::saveSignal() {
    if (savedCount < 10 && lastSignal.rawLen > 0) {
        savedSignals[savedCount] = lastSignal;
        savedCount++;
        buzzer.success();
    }
}

int IRRemoteModule::getSavedCount() { return savedCount; }
IRSignal IRRemoteModule::getLastSignal() { return lastSignal; }
void IRRemoteModule::clearSaved() { savedCount = 0; }

void IRRemoteModule::update() {
    if (!recording) return;
    bool state = digitalRead(IR_RECV_PIN);
    unsigned long now = micros();
    unsigned long duration = now - lastPulse;

    if (duration > 100000) {
        if (pulseIdx > 10) stopRecord();
        return;
    }

    static bool lastState = HIGH;
    if (state != lastState && pulseIdx < IR_BUFFER_SIZE) {
        lastSignal.rawData[pulseIdx] = (uint16_t)duration;
        pulseIdx++;
        lastPulse = now;
        lastState = state;
    }
}