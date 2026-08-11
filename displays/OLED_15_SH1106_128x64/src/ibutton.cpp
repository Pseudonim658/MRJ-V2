#include "ibutton.h"

IButtonModule ibutton;

void IButtonModule::init() {
    if (initialized) return;
    pinMode(IBUTTON_PIN, INPUT_PULLUP);
    savedCount = 0;
    initialized = true;
    logger.log(LOG_INFO, "IBUTTON", "iButton initialized");
}

void IButtonModule::end() {
    initialized = false;
    pinMode(IBUTTON_PIN, INPUT);
}

bool IButtonModule::oneWireReset() {
    pinMode(IBUTTON_PIN, OUTPUT);
    digitalWrite(IBUTTON_PIN, LOW);
    delayMicroseconds(480);
    pinMode(IBUTTON_PIN, INPUT_PULLUP);
    delayMicroseconds(70);
    bool presence = !digitalRead(IBUTTON_PIN);
    delayMicroseconds(410);
    return presence;
}

void IButtonModule::oneWireWrite(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        pinMode(IBUTTON_PIN, OUTPUT);
        digitalWrite(IBUTTON_PIN, LOW);
        if (data & (1 << i)) {
            delayMicroseconds(5);
            pinMode(IBUTTON_PIN, INPUT_PULLUP);
            delayMicroseconds(55);
        } else {
            delayMicroseconds(60);
            pinMode(IBUTTON_PIN, INPUT_PULLUP);
            delayMicroseconds(5);
        }
    }
}

uint8_t IButtonModule::oneWireRead() {
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        pinMode(IBUTTON_PIN, OUTPUT);
        digitalWrite(IBUTTON_PIN, LOW);
        delayMicroseconds(2);
        pinMode(IBUTTON_PIN, INPUT_PULLUP);
        delayMicroseconds(10);
        if (digitalRead(IBUTTON_PIN)) data |= (1 << i);
        delayMicroseconds(50);
    }
    return data;
}

bool IButtonModule::readKey() {
    if (!initialized) return false;
    if (!oneWireReset()) return false;
    oneWireWrite(0x33);
    lastKey.keyStr = "";
    for (int i = 0; i < 8; i++) {
        lastKey.key[i] = oneWireRead();
        char hex[4];
        snprintf(hex, sizeof(hex), "%02X", lastKey.key[i]);
        lastKey.keyStr += hex;
        if (i < 7) lastKey.keyStr += ":";
    }
    logger.logCapture("IBUTTON", ("Key: " + lastKey.keyStr).c_str());
    buzzer.success();
    return true;
}

bool IButtonModule::emulateKey(int idx) {
    if (idx >= savedCount) return false;
    logger.log(LOG_INFO, "IBUTTON", ("Emulating: " + savedKeys[idx].keyStr).c_str());
    return true;
}

void IButtonModule::saveKey() {
    if (savedCount < 20 && lastKey.keyStr.length() > 0) {
        savedKeys[savedCount] = lastKey;
        savedCount++;
        buzzer.success();
    }
}

int IButtonModule::getSavedCount() { return savedCount; }
IButtonKey* IButtonModule::getSavedKeys() { return savedKeys; }
IButtonKey IButtonModule::getLastKey() { return lastKey; }
void IButtonModule::clearSaved() { savedCount = 0; }
void IButtonModule::update() {}