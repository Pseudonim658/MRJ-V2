#ifndef SUBGHZ_ANALYZER_H
#define SUBGHZ_ANALYZER_H

#include <Arduino.h>
#include "subghz.h"

struct SubGHzSignal {
    float frequency;
    String modulation;
    int rssi;
    uint8_t data[64];
    uint8_t dataLen;
};

class SubGHzAnalyzer {
public:
    void init();
    void setFrequency(float freq);
    void setModulation(String mod);
    bool receive();
    SubGHzSignal getLastSignal();
    void freqScan();

private:
    float frequency = 433.92f;
    String modulation = "2FSK";
    SubGHzSignal lastSignal;
};

extern SubGHzAnalyzer subGHzAnalyzer;

#endif