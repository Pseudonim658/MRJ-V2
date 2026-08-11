#ifndef CH9326_H
#define CH9326_H

#include <Arduino.h>

class CH9326Module {
public:
    bool begin(uint32_t baud = 9600);
    void end();
    bool available() const;
    void update();
    bool isInitialized() const { return initialized_; }

private:
    HardwareSerial serial_{2};
    bool initialized_ = false;
};

extern CH9326Module ch9326;

#endif