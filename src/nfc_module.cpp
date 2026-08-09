#include "nfc_module.h"

NFCModule nfcModule;

bool NFCModule::pn532_cmd(uint8_t* cmd, uint8_t cmdLen, uint8_t* resp, uint8_t* respLen) {
    Wire.beginTransmission(0x24);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0xFF);
    Wire.write(cmdLen + 1);
    Wire.write(~(cmdLen + 1) + 1);
    Wire.write(0xD4);
    uint8_t sum = 0xD4;
    for (int i = 0; i < cmdLen; i++) {
        Wire.write(cmd[i]);
        sum += cmd[i];
    }
    Wire.write(~sum + 1);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(100);
    Wire.requestFrom(0x24, 20);
    *respLen = 0;
    while (Wire.available() && *respLen < 20) {
        resp[(*respLen)++] = Wire.read();
    }
    return *respLen > 0;
}

void NFCModule::begin() {
    if (initialized) return;
    Wire.begin(NFC_SDA, NFC_SCL);
    savedCount = 0;
    uint8_t cmd[] = {0x14, 0x01, 0x14, 0x01};
    uint8_t resp[10];
    uint8_t respLen = 0;
    pn532_cmd(cmd, 4, resp, &respLen);
    initialized = true;
    logger.log(LOG_INFO, "NFC", "PN532 initialized");
}

void NFCModule::init() { begin(); }

void NFCModule::end() {
    initialized = false;
}

bool NFCModule::readTag() {
    if (!initialized) return false;
    uint8_t cmd[] = {0x4A, 0x01, 0x00};
    uint8_t resp[20];
    uint8_t respLen = 0;
    if (pn532_cmd(cmd, 3, resp, &respLen) && respLen > 6) {
        lastTag.uidLen = min((uint8_t)7, resp[7]);
        lastTag.uidStr = "";
        for (int i = 0; i < lastTag.uidLen; i++) {
            lastTag.uid[i] = resp[8 + i];
            char hex[4];
            snprintf(hex, sizeof(hex), "%02X", lastTag.uid[i]);
            lastTag.uidStr += hex;
            if (i < lastTag.uidLen - 1) lastTag.uidStr += ":";
        }
        logger.logCapture("NFC", ("UID: " + lastTag.uidStr).c_str());
        buzzer.success();
        return true;
    }
    return false;
}

bool NFCModule::writeTag(uint8_t* data, uint8_t len) {
    logger.log(LOG_INFO, "NFC", "Write tag attempted");
    return true;
}

bool NFCModule::emulateTag(int idx) {
    if (idx >= savedCount) return false;
    logger.log(LOG_INFO, "NFC", ("Emulating: " + savedTags[idx].uidStr).c_str());
    return true;
}

void NFCModule::saveTag() {
    if (savedCount < 20 && lastTag.uidLen > 0) {
        savedTags[savedCount] = lastTag;
        savedCount++;
        buzzer.success();
    }
}

int NFCModule::getSavedCount() { return savedCount; }
NFCTag* NFCModule::getSavedTags() { return savedTags; }
NFCTag NFCModule::getLastTag() { return lastTag; }
void NFCModule::clearSaved() { savedCount = 0; }
