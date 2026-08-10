#include "eeprom_manager.h"
#include "ir_remote.h"
#include "nfc_module.h"
#include "subghz.h"
#include "rfid_module.h"
#include "badusb.h"
#include "ibutton.h"
#include "touch_driver.h"

extern IRRemoteModule irRemote;
extern NFCModule nfcModule;
extern SubGHzModule subGHz;
extern RFIDModule rfidModule;
extern BadUSBModule badUSB;
extern IButtonModule ibutton;
extern TouchDriver touch;

EEPROMManager eeprom;

// ============================================================
// TEAM MUTUAL EXCLUSION
// Team A: CH9326 (BadUSB) + CC1101 (SubGHz)
// Team B: NFC + RFID
// If Team A ON -> Team B OFF
// If Team B ON -> Team A OFF
// NOTE: DISABLED for OLED builds (more free pins)
// ============================================================

static bool isTeamA(uint8_t moduleId) {
    return (moduleId == EE_MODULE_BADUSB) || (moduleId == EE_MODULE_CC1101);
}

static bool isTeamB(uint8_t moduleId) {
    return (moduleId == EE_MODULE_NFC) || (moduleId == EE_MODULE_RFID);
}

static void disableTeamA() {
    eeprom.setModuleEnabled(EE_MODULE_BADUSB, false);
    eeprom.setModuleEnabled(EE_MODULE_CC1101, false);
}

static void disableTeamB() {
    eeprom.setModuleEnabled(EE_MODULE_NFC, false);
    eeprom.setModuleEnabled(EE_MODULE_RFID, false);
}

void EEPROMManager::init() {
    EEPROM.begin(EEPROM_SIZE);
    readAll();
    if (!configured) resetToDefaults();
}

void EEPROMManager::readAll() {
    EEPROM.get(EE_WEB_USER, webUser);
    EEPROM.get(EE_WEB_PASS, webPass);
    EEPROM.get(EE_AP_SSID, apSsid);
    EEPROM.get(EE_AP_PASS, apPass);
    EEPROM.get(EE_NETHERCAP_SSID, nethercapSsid);
    displayType = EEPROM.read(EE_DISPLAY_TYPE);

    webUser[MAX_STR_LEN-1] = '\0';
    webPass[MAX_STR_LEN-1] = '\0';
    apSsid[MAX_STR_LEN-1] = '\0';
    apPass[MAX_STR_LEN-1] = '\0';
    nethercapSsid[MAX_STR_LEN-1] = '\0';

    for (int i = 0; i < 16; i++) {
        moduleFlags[i] = EEPROM.read(141 + i);
        if (moduleFlags[i] == 0xFF) moduleFlags[i] = 0;
    }

    configured = EEPROM.read(EE_FLAG_CONFIGURED) == 0xAA;
    if (displayType == 0xFF) displayType = MRJ_DISPLAY_TYPE;
    if (nethercapSsid[0] == 0xFF || nethercapSsid[0] == 0) {
        strcpy(nethercapSsid, DEFAULT_NETHERCAP_SSID);
    }
}

void EEPROMManager::writeAll() {
    EEPROM.put(EE_WEB_USER, webUser);
    EEPROM.put(EE_WEB_PASS, webPass);
    EEPROM.put(EE_AP_SSID, apSsid);
    EEPROM.put(EE_AP_PASS, apPass);
    EEPROM.put(EE_NETHERCAP_SSID, nethercapSsid);
    EEPROM.write(EE_DISPLAY_TYPE, displayType);
    EEPROM.write(EE_FLAG_CONFIGURED, 0xAA);

    for (int i = 0; i < 16; i++) {
        EEPROM.write(141 + i, moduleFlags[i]);
    }
    EEPROM.commit();
}

void EEPROMManager::resetToDefaults() {
    strcpy(webUser, DEFAULT_WEB_USER);
    strcpy(webPass, DEFAULT_WEB_PASS);
    strcpy(apSsid, DEFAULT_AP_SSID);
    strcpy(apPass, DEFAULT_AP_PASS);
    strcpy(nethercapSsid, DEFAULT_NETHERCAP_SSID);
    displayType = MRJ_DISPLAY_TYPE;
    for (int i = 0; i < 16; i++) moduleFlags[i] = 0;
    configured = true;
    writeAll();
}

String EEPROMManager::getWebUser() { return String(webUser); }
String EEPROMManager::getWebPass() { return String(webPass); }
String EEPROMManager::getApSsid() { return String(apSsid); }
String EEPROMManager::getApPass() { return String(apPass); }
String EEPROMManager::getNethercapSsid() { return String(nethercapSsid); }
uint8_t EEPROMManager::getDisplayType() { return displayType; }

void EEPROMManager::setWebUser(const char* val) {
    strncpy(webUser, val, MAX_STR_LEN-1);
    webUser[MAX_STR_LEN-1] = '\0';
    writeAll();
}
void EEPROMManager::setWebPass(const char* val) {
    strncpy(webPass, val, MAX_STR_LEN-1);
    webPass[MAX_STR_LEN-1] = '\0';
    writeAll();
}
void EEPROMManager::setApSsid(const char* val) {
    strncpy(apSsid, val, MAX_STR_LEN-1);
    apSsid[MAX_STR_LEN-1] = '\0';
    writeAll();
}
void EEPROMManager::setApPass(const char* val) {
    strncpy(apPass, val, MAX_STR_LEN-1);
    apPass[MAX_STR_LEN-1] = '\0';
    writeAll();
}
void EEPROMManager::setNethercapSsid(const char* val) {
    strncpy(nethercapSsid, val, MAX_STR_LEN-1);
    nethercapSsid[MAX_STR_LEN-1] = '\0';
    writeAll();
}
void EEPROMManager::setDisplayType(uint8_t type) {
    displayType = type;
    writeAll();
}

bool EEPROMManager::isApPasswordSet() {
    return EEPROM.read(EE_AP_PASS_SET) == 0xAA;
}

bool EEPROMManager::isModuleEnabled(uint8_t moduleId) {
    if (moduleId < EE_MODULE_IR_RECV || moduleId > EE_MODULE_IR_RECV + 15) return false;
    int idx = moduleId - EE_MODULE_IR_RECV;
    return moduleFlags[idx] == 1;
}

void EEPROMManager::applyModuleChange(uint8_t moduleId, bool enabled) {
    switch (moduleId) {
        case EE_MODULE_IR_SEND:
            if (enabled) irRemote.enableTx();
            else irRemote.disableTx();
            break;
        case EE_MODULE_NFC:
            if (enabled) nfcModule.begin();
            else nfcModule.end();
            break;
        case EE_MODULE_CC1101:
            if (enabled) subGHz.begin();
            else subGHz.end();
            break;
        case EE_MODULE_RFID:
            if (enabled) rfidModule.begin();
            else rfidModule.end();
            break;
        case EE_MODULE_BADUSB:
            if (enabled) badUSB.init();
            else badUSB.stop();
            break;
        case EE_MODULE_IBUTTON:
            if (enabled) ibutton.init();
            else ibutton.end();
            break;
        case EE_MODULE_TOUCH:
            if (enabled) touch.init();
            else touch.end();
            break;
        default:
            break;
    }
}

void EEPROMManager::setModuleEnabled(uint8_t moduleId, bool enabled) {
    // ============================================================
    // TEAM MUTUAL EXCLUSION LOGIC
    // Team A: CH9326 (BadUSB) + CC1101 (SubGHz)
    // Team B: NFC + RFID
    // OLED builds: NO mutex (all modules can run simultaneously)
    // ============================================================
    #ifndef MRJ_NO_TEAM_MUTEX
    if (enabled) {
        if (isTeamA(moduleId)) {
            // Enabling Team A -> disable Team B
            disableTeamB();
        } else if (isTeamB(moduleId)) {
            // Enabling Team B -> disable Team A
            disableTeamA();
        }
    }
    #endif

    int idx = moduleId - EE_MODULE_IR_RECV;
    if (idx < 0 || idx >= 16) return;
    moduleFlags[idx] = enabled ? 1 : 0;
    writeAll();

    applyModuleChange(moduleId, enabled);
}
