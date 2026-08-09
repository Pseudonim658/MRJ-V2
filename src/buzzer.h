#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "hardware_pinout.h"
#include "config.h"

class BuzzerModule {
public:
    void init();
    void beep(uint16_t freq = 2000, uint16_t duration = 50);
    void click();
    void success();
    void error();
    void alarm();
    void setEnabled(bool en);
    bool isEnabled();
    void setVolume(uint8_t vol);
    uint8_t getVolume();
    void update();

private:
    bool enabled = true;
    uint8_t volume = 128;
    bool playing = false;
    unsigned long beepEnd = 0;
    uint8_t alarmStep = 0;
    unsigned long alarmNext = 0;
    bool alarmActive = false;
};

extern BuzzerModule buzzer;

#endif
