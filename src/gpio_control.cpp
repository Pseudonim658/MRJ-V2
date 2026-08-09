#include "gpio_control.h"

GPIOControlModule gpioControl;

void GPIOControlModule::init() {
    pinCount = 0;
    logger.log(LOG_INFO, "GPIO", "GPIO Control initialized");
}

void GPIOControlModule::setPin(uint8_t pin, bool output, const char* label) {
    if (pinCount >= 8) return;
    if (!ReservedPinManager::getInstance().isSafeForUser(pin)) {
        logger.log(LOG_WARN, "GPIO", ("Pin " + String(pin) + " is reserved or invalid").c_str());
        return;
    }
    pins[pinCount].pin = pin;
    pins[pinCount].isOutput = output;
    pins[pinCount].state = false;
    pins[pinCount].label = String(label);
    pinMode(pin, output ? OUTPUT : INPUT);
    pinCount++;
}

void GPIOControlModule::togglePin(uint8_t pin) {
    for (int i = 0; i < pinCount; i++) {
        if (pins[i].pin == pin && pins[i].isOutput) {
            pins[i].state = !pins[i].state;
            digitalWrite(pin, pins[i].state);
            buzzer.click();
            logger.log(LOG_INFO, "GPIO", ("Pin " + String(pin) + " -> " + String(pins[i].state)).c_str());
            return;
        }
    }
}

void GPIOControlModule::writePin(uint8_t pin, bool state) {
    for (int i = 0; i < pinCount; i++) {
        if (pins[i].pin == pin && pins[i].isOutput) {
            pins[i].state = state;
            digitalWrite(pin, state);
            return;
        }
    }
}

bool GPIOControlModule::readPin(uint8_t pin) {
    return digitalRead(pin);
}

String GPIOControlModule::getInfo() {
    String info = "";
    for (int i = 0; i < pinCount; i++) {
        info += "GPIO" + String(pins[i].pin) + " [" + pins[i].label + "] ";
        info += pins[i].isOutput ? "OUT" : "IN";
        info += " = " + String(pins[i].isOutput ? pins[i].state : digitalRead(pins[i].pin));
        info += "\n";
    }
    return info;
}

GPIOPin* GPIOControlModule::getPins() { return pins; }
int GPIOControlModule::getPinCount() { return pinCount; }
