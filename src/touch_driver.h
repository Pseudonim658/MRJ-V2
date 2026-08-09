#ifndef TOUCH_DRIVER_H
#define TOUCH_DRIVER_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "hardware_pinout.h"

class TouchDriver {
public:
    void init();
    void end();
    bool isTouched();
    void getPoint(int &x, int &y);
    bool isPressed();

private:
    bool xptPresent = false;
    bool cstPresent = false;
    int touchX = 0, touchY = 0;
    bool touched = false;
    bool initialized = false;
    unsigned long lastTouch = 0;
};

extern TouchDriver touch;

#endif
