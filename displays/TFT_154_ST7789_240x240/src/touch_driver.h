#ifndef TOUCH_DRIVER_H
#define TOUCH_DRIVER_H

#include <Arduino.h>
#include <SPI.h>
#include "hardware_pinout.h"

class TouchDriver {
public:
    void init();
    void begin();
    void end();
    void update();
    bool isTouched();
    void getPoint(int &x, int &y);
    bool isPressed();

private:
    int touchX = 0, touchY = 0;
    bool touched = false;
    bool initialized = false;
};

extern TouchDriver touch;

#endif
