#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"

class EEPROMManager {
public:
    void init();
    void resetToDefaults();

    String getWebUser();
    String getWebPass();
    String getApSsid();
    String getApPass();

    void setWebUser(const char* val);
    void setWebPass(const char* val);
    void setApSsid(const char* val);
    void setApPass(const char* val);

    bool isApPasswordSet();

    String getNethercapSsid();
    void setNethercapSsid(const char* val);

    bool isModuleEnabled(uint8_t moduleId);
    void setModuleEnabled(uint8_t moduleId, bool enabled);

    uint8_t getDisplayType();
    void setDisplayType(uint8_t type);

private:
    char webUser[MAX_STR_LEN];
    char webPass[MAX_STR_LEN];
    char apSsid[MAX_STR_LEN];
    char apPass[MAX_STR_LEN];
    char nethercapSsid[MAX_STR_LEN];
    uint8_t displayType = MRJ_DISPLAY_TYPE;
    bool configured = false;
    uint8_t moduleFlags[16];

    void readAll();
    void writeAll();
    void applyModuleChange(uint8_t moduleId, bool enabled);
};

extern EEPROMManager eeprom;

#endif