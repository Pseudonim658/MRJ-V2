#include "touch_driver.h"
#include "logger.h"

TouchDriver touch;

void TouchDriver::init() {
    if (TOUCH_CS < 0 && TOUCH_IRQ < 0) {
        logger.log(LOG_WARN, "TOUCH", "Touch disabled (pins -1)");
        return;
    }
    initialized = true;
    logger.log(LOG_INFO, "TOUCH", "Touch driver initialized (stub)");
}

void TouchDriver::end() {
    initialized = false;
}

bool TouchDriver::isTouched() {
    return initialized && touched;
}

void TouchDriver::getPoint(int &x, int &y) {
    x = touchX;
    y = touchY;
}

bool TouchDriver::isPressed() {
    return isTouched();
}