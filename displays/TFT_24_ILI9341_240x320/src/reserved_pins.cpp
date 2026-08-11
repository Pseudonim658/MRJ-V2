#include "reserved_pins.h"
#include "hardware_pinout.h"
#include "config.h"

ReservedPinManager& ReservedPinManager::getInstance() {
    static ReservedPinManager manager;
    return manager;
}

void ReservedPinManager::init() {
    for (size_t i = 0; i < MAX_TRACKED_PINS; ++i) used_[i] = false;

    int pins[] = {
        BTN_UP, BTN_DOWN, BTN_SELECT, BTN_BACK,
        BUZZER_PIN,
        DISPLAY_CS, DISPLAY_DC, DISPLAY_RST,
        HSPI_SCK, HSPI_MISO, HSPI_MOSI, SD_CS,
        VSPI_SCK, VSPI_MISO, VSPI_MOSI,
        NFC_SDA, NFC_SCL, NFC_IRQ,
        IR_RECV_PIN, IR_SEND_PIN,
        IBUTTON_PIN,
        ADC_BATTERY_PIN
    };

    for (int pin : pins) {
        if (pin >= 0 && pin < (int)MAX_TRACKED_PINS) {
            used_[pin] = true;
        }
    }
}

bool ReservedPinManager::isReserved(int pin) const {
    return pin >= 0 && pin < (int)MAX_TRACKED_PINS && used_[pin];
}

bool ReservedPinManager::isSafeForUser(int pin) const {
    if (pin < 0 || pin >= (int)MAX_TRACKED_PINS) return false;
    if (isReserved(pin)) return false;
    if (isInputOnly(pin)) return false;
    return true;
}

bool ReservedPinManager::isInputOnly(int pin) const {
    return (pin >= 34 && pin <= 39);
}

void initReservedPins() {
    ReservedPinManager::getInstance().init();
}

bool validateHardwarePinout() {
    auto& r = ReservedPinManager::getInstance();
    r.init();

    bool seen[40] = {false};

    int pins[] = {
        BTN_UP, BTN_DOWN, BTN_SELECT, BTN_BACK,
        BUZZER_PIN,
        DISPLAY_CS, DISPLAY_DC, DISPLAY_RST,
        HSPI_SCK, HSPI_MISO, HSPI_MOSI, SD_CS,
        VSPI_SCK, VSPI_MISO, VSPI_MOSI,
        NFC_SDA, NFC_SCL, NFC_IRQ,
        IR_RECV_PIN, IR_SEND_PIN,
        IBUTTON_PIN,
        ADC_BATTERY_PIN
    };

    for (int pin : pins) {
        if (pin < 0) continue;
        if (seen[pin]) {
            Serial.printf("[ERROR] GPIO conflict on pin %d\n", pin);
            return false;
        }
        seen[pin] = true;
    }

    if (IR_SEND_PIN >= 34 && IR_SEND_PIN <= 39) {
        Serial.printf("[ERROR] IR_SEND_PIN on input-only GPIO %d\n", IR_SEND_PIN);
        return false;
    }

    return true;
}