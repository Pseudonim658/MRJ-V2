#ifndef IR_REMOTE_H
#define IR_REMOTE_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

struct IRSignal {
    uint16_t rawData[IR_BUFFER_SIZE];
    uint16_t rawLen;
    String protocol;
    uint32_t code;
};

class IRRemoteModule {
public:
    void init();
    void startRecord();
    void stopRecord();
    bool isRecording();
    bool hasSignal();
    void playSignal(int idx = -1);
    void saveSignal();
    int getSavedCount();
    IRSignal getLastSignal();
    void clearSaved();
    void update();

    void enableTx();
    void disableTx();

private:
    IRSignal lastSignal;
    IRSignal savedSignals[10];
    int savedCount = 0;
    bool recording = false;
    unsigned long lastPulse = 0;
    uint16_t pulseIdx = 0;
    bool txEnabled = false;
};

extern IRRemoteModule irRemote;

#endif