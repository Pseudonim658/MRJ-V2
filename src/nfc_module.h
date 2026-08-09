#ifndef NFC_MODULE_H
#define NFC_MODULE_H

#include <Arduino.h>
#include <Wire.h>
#include "hardware_pinout.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

struct NFCTag {
    uint8_t uid[7];
    uint8_t uidLen;
    String uidStr;
};

class NFCModule {
public:
    void init();
    bool readTag();
    bool writeTag(uint8_t* data, uint8_t len);
    bool emulateTag(int idx);
    void saveTag();
    int getSavedCount();
    NFCTag* getSavedTags();
    NFCTag getLastTag();
    void clearSaved();
    void begin();
    void end();

private:
    NFCTag lastTag;
    NFCTag savedTags[20];
    int savedCount = 0;
    bool initialized = false;

    bool pn532_cmd(uint8_t* cmd, uint8_t cmdLen, uint8_t* resp, uint8_t* respLen);
};

extern NFCModule nfcModule;

#endif
