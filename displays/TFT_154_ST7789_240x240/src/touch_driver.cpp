#include "touch_driver.h"
#include "hardware_pinout.h"
#include "logger.h"
#include <SPI.h>

TouchDriver touch;

// Basic XPT2046 / resistive touch over SPI
#define XPT_CMD_X       0x90
#define XPT_CMD_Y       0xD0
#define XPT_CMD_Z1      0xB0

static uint16_t xpt_read(uint8_t cmd) {
    if (TOUCH_CS < 0) return 0;
    digitalWrite(TOUCH_CS, LOW);
    SPI.transfer(cmd);
    uint16_t v = SPI.transfer(0x00) << 8;
    v |= SPI.transfer(0x00);
    digitalWrite(TOUCH_CS, HIGH);
    return v >> 3; // 12-bit
}

void TouchDriver::begin() {
    if (initialized) return;
    if (TOUCH_CS < 0) {
        logger.log(LOG_WARN, "TOUCH", "Touch pins disabled");
        return;
    }
    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);
    if (TOUCH_IRQ >= 0) {
        pinMode(TOUCH_IRQ, INPUT_PULLUP);
    }
    // SPI already started by display / other modules
    SPI.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI);
    initialized = true;
    touched = false;
    touchX = touchY = 0;
    logger.log(LOG_INFO, "TOUCH", "Touch driver ready");
}

void TouchDriver::init() { begin(); }

void TouchDriver::end() {
    if (TOUCH_CS >= 0) digitalWrite(TOUCH_CS, HIGH);
    initialized = false;
}

void TouchDriver::update() {
    if (!initialized) return;
    bool irq = (TOUCH_IRQ < 0) || (digitalRead(TOUCH_IRQ) == LOW);
    if (!irq) {
        touched = false;
        return;
    }
    // Average a few samples
    uint32_t sumX = 0, sumY = 0;
    const int samples = 4;
    for (int i = 0; i < samples; i++) {
        sumX += xpt_read(XPT_CMD_X);
        sumY += xpt_read(XPT_CMD_Y);
    }
    uint16_t rawX = sumX / samples;
    uint16_t rawY = sumY / samples;
    // Simple calibration mapping (adjust for your panel)
    // raw typically 200-3800
    touchX = map(constrain(rawX, 200, 3800), 200, 3800, 0, 320);
    touchY = map(constrain(rawY, 200, 3800), 200, 3800, 0, 240);
    touched = true;
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
