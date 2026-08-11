#ifndef IBUTTON_H
#define IBUTTON_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

struct IButtonKey {
    uint8_t key[8];
    String keyStr;
};

class IButtonModule {
public:
    void init();
    void end();
    bool readKey();
    bool emulateKey(int idx);
    void saveKey();
    int getSavedCount();
    IButtonKey* getSavedKeys();
    IButtonKey getLastKey();
    void clearSaved();
    void update();

private:
    IButtonKey lastKey;
    IButtonKey savedKeys[20];
    int savedCount = 0;
    bool initialized = false;

    bool oneWireReset();
    void oneWireWrite(uint8_t data);
    uint8_t oneWireRead();
};

extern IButtonModule ibutton;

#endif