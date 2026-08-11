#ifndef IR_DECODER_H
#define IR_DECODER_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

struct IRDecodedSignal {
    String protocol;
    uint32_t address;
    uint32_t command;
    uint16_t rawLen;
    bool repeat;
};

class IRDecoder {
public:
    void init();
    bool decode();
    IRDecodedSignal getLastDecoded();

private:
    IRDecodedSignal lastSignal;
    uint16_t rawData[IR_BUFFER_SIZE];
    uint16_t rawLen = 0;
    unsigned long lastPulse = 0;
    bool recording = false;

    bool decodeNEC(uint16_t* data, uint16_t len);
    bool decodeSony(uint16_t* data, uint16_t len);
    bool decodeRC5(uint16_t* data, uint16_t len);
    void recordPulse();
};

extern IRDecoder irDecoder;

#endif