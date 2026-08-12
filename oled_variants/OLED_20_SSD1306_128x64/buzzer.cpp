#include "buzzer.h"

BuzzerModule buzzer;

void BuzzerModule::init() {
    enabled = BUZZER_ENABLED_DEFAULT;
    volume = BUZZER_VOLUME_DEFAULT;
    playing = false;
    alarmActive = false;

    ledcSetup(0, BUZZER_FREQ, BUZZER_RES);
    ledcAttachPin(BUZZER_PIN, 0);
    ledcWrite(0, 0);
}

void BuzzerModule::beep(uint16_t freq, uint16_t duration) {
    if (!enabled) return;
    ledcChangeFrequency(0, freq, BUZZER_RES);
    ledcWrite(0, volume);
    playing = true;
    beepEnd = millis() + duration;
}

void BuzzerModule::click() { beep(4000, 20); }
void BuzzerModule::success() { beep(2000, 100); }
void BuzzerModule::error() { beep(500, 200); }

void BuzzerModule::alarm() {
    alarmActive = true;
    alarmStep = 0;
    alarmNext = millis();
}

void BuzzerModule::setEnabled(bool en) {
    enabled = en;
    if (!en) {
        ledcWrite(0, 0);
        playing = false;
        alarmActive = false;
    }
}
bool BuzzerModule::isEnabled() { return enabled; }
void BuzzerModule::setVolume(uint8_t vol) { volume = vol; }
uint8_t BuzzerModule::getVolume() { return volume; }

void BuzzerModule::update() {
    if (playing && (long)(millis() - beepEnd) >= 0) {
        ledcWrite(0, 0);
        playing = false;
    }
    if (alarmActive && (long)(millis() - alarmNext) >= 0) {
        if (alarmStep < 6) {
            if (alarmStep % 2 == 0) beep(3000, 150);
            alarmStep++;
            alarmNext = millis() + 200;
        } else {
            alarmActive = false;
        }
    }
}
