#ifndef RFID_125KHZ_H
#define RFID_125KHZ_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "logger.h"
#include "buzzer.h"

struct RFID125Card {
    String uidStr;
    uint8_t uid[5];
    String type;
};

class RFID125kHz {
public:
    void init(uint8_t rxPin = RFID125_RX, uint8_t txPin = RFID125_TX);
    bool readCard();
    RFID125Card getLastCard();

private:
    uint8_t rxPin_;
    uint8_t txPin_;
    RFID125Card lastCard;
    String readBuffer = "";
    String parseUID(String data);
};

extern RFID125kHz rfid125;

#endif