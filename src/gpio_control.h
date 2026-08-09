#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <Arduino.h>
#include "logger.h"
#include "buzzer.h"
#include "reserved_pins.h"

struct GPIOPin {
    uint8_t pin;
    bool isOutput;
    bool state;
    String label;
};

class GPIOControlModule {
public:
    void init();
    void setPin(uint8_t pin, bool output, const char* label = "");
    void togglePin(uint8_t pin);
    void writePin(uint8_t pin, bool state);
    bool readPin(uint8_t pin);
    String getInfo();
    GPIOPin* getPins();
    int getPinCount();

private:
    GPIOPin pins[8];
    int pinCount = 0;
};

extern GPIOControlModule gpioControl;

#endif
