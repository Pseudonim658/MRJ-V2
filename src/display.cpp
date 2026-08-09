#include "display.h"
#include "logger.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

DisplayModule display;

DisplayModule::DisplayModule() {}

DisplayModule::~DisplayModule() {
    if (driver) {
        delete (Adafruit_GFX*)driver;
        driver = nullptr;
    }
}

bool DisplayModule::begin() {
    if (type != DISPLAY_TYPE_ST7735) {
        logger.log(LOG_ERROR, "DISPLAY", "Only ST7735 is supported in this build");
        return false;
    }

    SPI.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, DISPLAY_CS);

    Adafruit_ST7735* tft = new Adafruit_ST7735(DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);
    tft->initR(INITR_BLACKTAB);
    tft->setRotation(0);
    tft->fillScreen(THEME_BG);

    driver = tft;
    width = 128;
    height = 160;
    initialized = true;

    logger.log(LOG_INFO, "DISPLAY", "ST7735 TFT initialized");
    return true;
}

void DisplayModule::clear() {
    if (!driver) return;
    ((Adafruit_GFX*)driver)->fillScreen(THEME_BG);
}

void DisplayModule::update() {}

void DisplayModule::drawString(int x, int y, const char* text, uint16_t color) {
    if (!driver || !text) return;
    Adafruit_GFX* t = (Adafruit_GFX*)driver;
    t->setCursor(x, y);
    t->setTextColor(color);
    t->print(text);
}

void DisplayModule::drawStringCenter(int y, const char* text, uint16_t color) {
    if (!driver || !text) return;
    Adafruit_GFX* t = (Adafruit_GFX*)driver;
    int16_t x1, y1;
    uint16_t w, h;
    t->setTextColor(color);
    t->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    t->setCursor((width - w) / 2, y);
    t->print(text);
}

void DisplayModule::drawPixel(int x, int y, uint16_t color) {
    if (!driver) return;
    ((Adafruit_GFX*)driver)->drawPixel(x, y, color);
}

void DisplayModule::drawLine(int x1, int y1, int x2, int y2, uint16_t color) {
    if (!driver) return;
    ((Adafruit_GFX*)driver)->drawLine(x1, y1, x2, y2, color);
}

void DisplayModule::drawRect(int x, int y, int w, int h, uint16_t color) {
    if (!driver) return;
    ((Adafruit_GFX*)driver)->drawRect(x, y, w, h, color);
}

void DisplayModule::fillRect(int x, int y, int w, int h, uint16_t color) {
    if (!driver) return;
    ((Adafruit_GFX*)driver)->fillRect(x, y, w, h, color);
}

void DisplayModule::drawBitmap(int x, int y, const uint8_t* bitmap, int w, int h, uint16_t color) {
    if (!driver || !bitmap) return;
    ((Adafruit_GFX*)driver)->drawBitmap(x, y, bitmap, w, h, color);
}

void DisplayModule::showSplash() {
    clear();
    drawStringCenter(30, "mrj v" FIRMWARE_VERSION, THEME_TEXT);
    delay(2000);
}

void DisplayModule::showStatus(const char* line1, const char* line2, const char* line3) {
    clear();
    drawString(0, 10, line1);
    if (strlen(line2) > 0) drawString(0, 30, line2);
    if (strlen(line3) > 0) drawString(0, 50, line3);
}

void DisplayModule::showIP(const char* ip) {
    drawString(0, height - 10, ip);
}

void DisplayModule::showBootProgress(int percent, const char* module) {
    clear();
    drawStringCenter(height / 4, FIRMWARE_NAME);
    drawStringCenter(height / 4 + 20, "v" FIRMWARE_VERSION);

    int barWidth = width - 40;
    int barHeight = 10;
    int barX = 20;
    int barY = height / 2 + 10;
    drawRect(barX, barY, barWidth, barHeight);
    fillRect(barX + 2, barY + 2, (barWidth - 4) * percent / 100, barHeight - 4);

    char percentStr[8];
    sprintf(percentStr, "%d%%", percent);
    drawStringCenter(barY + barHeight + 15, percentStr);
    drawStringCenter(barY + barHeight + 30, module);
}
