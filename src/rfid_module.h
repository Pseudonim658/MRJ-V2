#ifndef RFID_MODULE_H
#define RFID_MODULE_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "logger.h"
#include "buzzer.h"

struct RFIDTag {
    uint8_t uid[10];
    uint8_t uidLen;
    String uidStr;
};

class RFIDModule {
public:
    void init();
    void begin();
    void end();
    bool readCard();
    void saveCard();
    int getSavedCount();
    RFIDTag* getSavedCards();
    RFIDTag getLastCard();
    void clearSaved();

private:
    RFIDTag lastCard;
    RFIDTag savedCards[20];
    int savedCount = 0;
    bool initialized = false;
};

extern RFIDModule rfidModule;

#endif
