#ifndef BADUSB_H
#define BADUSB_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

class BadUSBModule {
public:
    void init();
    void typeString(const char* str);
    void pressKey(uint8_t key);
    void releaseKey();
    void executeScript(const char* script);
    void executeFromSD(const char* filename);
    void stop();
    bool isRunning();

private:
    bool running = false;
    HardwareSerial serial_{2};
    void processLine(const char* line);
};

extern BadUSBModule badUSB;

#endif
