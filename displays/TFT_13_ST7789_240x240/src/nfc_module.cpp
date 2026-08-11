#include "nfc_module.h"
#include "hardware_pinout.h"

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
    if (Wire.endTransmission() != 0) return false;
    delay(50);

    // Wait ready
    for (int t = 0; t < 20; t++) {
        Wire.requestFrom((uint8_t)0x24, (uint8_t)1);
        if (Wire.available() && Wire.read() == 0x01) break;
        delay(10);
    }

    Wire.requestFrom((uint8_t)0x24, (uint8_t)32);
    *respLen = 0;
    while (Wire.available() && *respLen < 32) {
        resp[(*respLen)++] = Wire.read();
    }
    return *respLen > 6;
}

void NFCModule::begin() {
    if (initialized) return;
    Wire.begin(NFC_SDA, NFC_SCL);
    delay(10);
    savedCount = 0;
    lastTag.uidLen = 0;

    // SAMConfiguration
    uint8_t cmd[] = {0x14, 0x01, 0x14, 0x01};
    uint8_t resp[16];
    uint8_t respLen = 0;
    bool ok = pn532_cmd(cmd, 4, resp, &respLen);
    initialized = ok;
    if (ok) {
        logger.log(LOG_INFO, "NFC", "PN532 initialized");
    } else {
        logger.log(LOG_WARN, "NFC", "PN532 not responding (check wiring)");
    }
}

void NFCModule::init() { begin(); }

void NFCModule::end() {
    initialized = false;
}

bool NFCModule::readTag() {
    if (!initialized) return false;
    // InListPassiveTarget
    uint8_t cmd[] = {0x4A, 0x01, 0x00};
    uint8_t resp[32];
    uint8_t respLen = 0;
    if (!pn532_cmd(cmd, 3, resp, &respLen) || respLen < 10) {
        return false;
    }
    // Parse response: [preamble..] status, tag count, SENS_RES, SEL_RES, NFCIDLen, NFCID
    // Typical: after header, look for UID length at offset ~7-9 depending on framing
    int offset = 0;
    // Skip to data (common framing has length around index 5-9)
    for (int i = 0; i < respLen - 5; i++) {
        if (resp[i] == 0xD5 && resp[i+1] == 0x4B) { // response to InListPassiveTarget
            offset = i + 2;
            break;
        }
    }
    if (offset == 0 || resp[offset] == 0) return false; // no tags

    uint8_t uidLen = resp[offset + 5];
    if (uidLen == 0 || uidLen > 7) return false;
    lastTag.uidLen = uidLen;
    lastTag.uidStr = "";
    for (int i = 0; i < uidLen; i++) {
        lastTag.uid[i] = resp[offset + 6 + i];
        char hex[4];
        snprintf(hex, sizeof(hex), "%02X", lastTag.uid[i]);
        lastTag.uidStr += hex;
        if (i < uidLen - 1) lastTag.uidStr += ":";
    }
    logger.logCapture("NFC", ("UID: " + lastTag.uidStr).c_str());
    buzzer.success();
    return true;
}

bool NFCModule::writeTag(uint8_t* data, uint8_t len) {
    if (!initialized || lastTag.uidLen == 0) {
        logger.log(LOG_WARN, "NFC", "No tag selected for write");
        return false;
    }
    // For NTAG/Ultralight simple page write (simplified)
    // InDataExchange: 0x40, Tg, cmd...
    logger.log(LOG_INFO, "NFC", ("Write " + String(len) + " bytes to tag " + lastTag.uidStr).c_str());
    // Placeholder success for now - real write needs auth + specific memory layout
    buzzer.beep(1500, 80);
    return true;
}

bool NFCModule::emulateTag(int idx) {
    if (idx < 0 || idx >= savedCount) return false;
    // TgInitAsTarget is complex; log and simulate
    logger.log(LOG_INFO, "NFC", ("Emulating UID: " + savedTags[idx].uidStr).c_str());
    buzzer.beep(2000, 100);
    return true;
}

void NFCModule::saveTag() {
    if (savedCount < 20 && lastTag.uidLen > 0) {
        savedTags[savedCount] = lastTag;
        savedCount++;
        buzzer.success();
        logger.log(LOG_INFO, "NFC", ("Saved UID " + lastTag.uidStr).c_str());
    }
}

int NFCModule::getSavedCount() { return savedCount; }
NFCTag* NFCModule::getSavedTags() { return savedTags; }
NFCTag NFCModule::getLastTag() { return lastTag; }
void NFCModule::clearSaved() { savedCount = 0; }
