#include "ch9326.h"
#include "hardware_pinout.h"
#include "logger.h"

CH9326Module ch9326;

bool CH9326Module::begin(uint32_t baud) {
    if (CH9326_TX < 0 || CH9326_RX < 0) {
        logger.log(LOG_WARN, "CH9326", "CH9326 disabled (pins -1)");
        return false;
    }
    serial_.begin(baud, SERIAL_8N1, CH9326_RX, CH9326_TX);
    initialized_ = true;
    logger.log(LOG_INFO, "CH9326", "CH9326 initialized");
    return true;
}

void CH9326Module::end() {
    if (initialized_) {
        serial_.end();
        initialized_ = false;
    }
}

bool CH9326Module::available() const {
    return initialized_ && serial_.available() > 0;
}

void CH9326Module::update() {
    if (!initialized_) return;
    while (serial_.available()) {
        (void)serial_.read();
    }
}