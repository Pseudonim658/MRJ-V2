#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.h"
#include "hardware_pinout.h"

#include <Wire.h>
#include <U8g2lib.h>

class DisplayModule {
public:
    DisplayModule();
    ~DisplayModule();

    bool begin();
    void clear();
    void update();
    void drawString(int x, int y, const char* text, uint16_t color = THEME_TEXT);
    void drawStringCenter(int y, const char* text, uint16_t color = THEME_TEXT);
    void drawPixel(int x, int y, uint16_t color = THEME_TEXT);
    void drawLine(int x1, int y1, int x2, int y2, uint16_t color = THEME_TEXT);
    void drawRect(int x, int y, int w, int h, uint16_t color = THEME_TEXT);
    void fillRect(int x, int y, int w, int h, uint16_t color = THEME_TEXT);
    void drawBitmap(int x, int y, const uint8_t* bitmap, int w, int h, uint16_t color = THEME_TEXT);

    void showSplash();
    void showStatus(const char* line1, const char* line2 = "", const char* line3 = "");
    void showIP(const char* ip);
    void showBootProgress(int percent, const char* module);

    bool isInitialized() const { return initialized; }
    uint16_t getWidth() const { return width; }
    uint16_t getHeight() const { return height; }
    uint8_t getType() const { return type; }

private:
    bool initOLED();

    void* driver = nullptr;
    uint8_t type = MRJ_DISPLAY_TYPE;
    uint16_t width = MRJ_DISPLAY_WIDTH;
    uint16_t height = MRJ_DISPLAY_HEIGHT;
    bool initialized = false;
};

extern DisplayModule display;

#endif
