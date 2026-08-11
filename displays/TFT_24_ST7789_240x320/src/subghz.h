#ifndef SUBGHZ_H
#define SUBGHZ_H

#include <Arduino.h>
#include <SPI.h>
#include "hardware_pinout.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

class SubGHzModule {
public:
    void init();
    void begin();
    void end();
    void setFrequency(float freq);
    float getFrequency();
    void startReceive();
    void stopReceive();
    void sendData(uint8_t* data, uint8_t len);
    void sendLast();
    void freqScan();
    bool isReceiving();
    bool hasData();
    uint8_t* getLastData();
    uint8_t getLastDataLen();
    void update();

private:
    float frequency = 433.92f;
    bool receiving = false;
    bool dataReady = false;
    uint8_t lastData[64];
    uint8_t lastDataLen = 0;
    uint8_t savedSignals[10][64];
    uint8_t savedLens[10];
    int savedCount = 0;
    bool initialized = false;

    void cc1101_write(uint8_t addr, uint8_t data);
    uint8_t cc1101_read(uint8_t addr);
    void cc1101_strobe(uint8_t strobe);
};

extern SubGHzModule subGHz;

#endif