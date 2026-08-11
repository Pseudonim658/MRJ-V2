#include "display.h"
#include "logger.h"

DisplayModule display;

DisplayModule::DisplayModule() {}

DisplayModule::~DisplayModule() {
    if (driver) {
        #ifdef MRJ_DISPLAY_TFT
            delete (Adafruit_GFX*)driver;
        #elif defined(MRJ_DISPLAY_OLED)
            #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
                delete (Adafruit_SSD1306*)driver;
            #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SH1106 || MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SH1107 || MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1327
                delete (U8G2*)driver;
            #endif
        #endif
        driver = nullptr;
    }
}

bool DisplayModule::begin() {
    #ifdef MRJ_DISPLAY_TFT
        return initTFT();
    #elif defined(MRJ_DISPLAY_OLED)
        return initOLED();
    #else
        logger.log(LOG_ERROR, "DISPLAY", "No display type defined");
        return false;
    #endif
}

// ============================================================
// TFT INITIALIZATION
// ============================================================
#ifdef MRJ_DISPLAY_TFT
bool DisplayModule::initTFT() {
    SPI.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, DISPLAY_CS);

    #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_ST7735
        Adafruit_ST7735* tft = new Adafruit_ST7735(DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);
        tft->initR(INITR_BLACKTAB);
        tft->setRotation(0);
    #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_ILI9341
        Adafruit_ILI9341* tft = new Adafruit_ILI9341(DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);
        tft->begin();
        tft->setRotation(0);
    #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_ILI9488
        Adafruit_ILI9488* tft = new Adafruit_ILI9488(DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);
        tft->begin();
        tft->setRotation(0);
    #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_ST7789
        Adafruit_ST7789* tft = new Adafruit_ST7789(DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);
        // For 240x240 square: init(240, 240)
        // For 240x320: init(240, 320)
        tft->init(width, height);
        tft->setRotation(0);
    #endif

    tft->fillScreen(THEME_BG);
    driver = tft;
    initialized = true;
    logger.log(LOG_INFO, "DISPLAY", (String("TFT initialized (") + width + "x" + height + ")").c_str());
    return true;
}
#endif

// ============================================================
// OLED INITIALIZATION
// ============================================================
#ifdef MRJ_DISPLAY_OLED
bool DisplayModule::initOLED() {
    Wire.begin(DISPLAY_SDA, DISPLAY_SCL);

    #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
        Adafruit_SSD1306* oled = new Adafruit_SSD1306(width, height, &Wire, DISPLAY_RST);
        if (!oled->begin(SSD1306_SWITCHCAPVCC, DISPLAY_I2C_ADDR)) {
            logger.log(LOG_ERROR, "DISPLAY", "SSD1306 init failed");
            delete oled;
            return false;
        }
        oled->clearDisplay();
        oled->setTextSize(1);
        oled->setTextColor(SSD1306_WHITE);
        oled->display();
        driver = oled;

    #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SH1106
        // U8G2_SH1106_128X64_NONAME_F_HW_I2C
        U8G2_SH1106_128X64_NONAME_F_HW_I2C* oled = new U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
        oled->begin();
        oled->clearBuffer();
        oled->setFont(u8g2_font_6x10_tf);
        oled->sendBuffer();
        driver = oled;

    #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SH1107
        // U8G2_SH1107_128X128_F_HW_I2C
        U8G2_SH1107_128X128_F_HW_I2C* oled = new U8G2_SH1107_128X128_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
        oled->begin();
        oled->clearBuffer();
        oled->setFont(u8g2_font_6x10_tf);
        oled->sendBuffer();
        driver = oled;

    #elif MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1327
        // U8G2_SSD1327_EA_W128128_F_HW_I2C
        U8G2_SSD1327_EA_W128128_F_HW_I2C* oled = new U8G2_SSD1327_EA_W128128_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
        oled->begin();
        oled->clearBuffer();
        oled->setFont(u8g2_font_6x10_tf);
        oled->sendBuffer();
        driver = oled;
    #endif

    initialized = true;
    logger.log(LOG_INFO, "DISPLAY", (String("OLED initialized (") + width + "x" + height + ")").c_str());
    return true;
}
#endif

// ============================================================
// DRAWING PRIMITIVES
// ============================================================
void DisplayModule::clear() {
    if (!driver) return;
    #ifdef MRJ_DISPLAY_TFT
        ((Adafruit_GFX*)driver)->fillScreen(THEME_BG);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->clearDisplay();
        #else
            ((U8G2*)driver)->clearBuffer();
        #endif
    #endif
}

void DisplayModule::update() {
    if (!driver) return;
    #ifdef MRJ_DISPLAY_OLED
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->display();
        #else
            ((U8G2*)driver)->sendBuffer();
        #endif
    #endif
}

void DisplayModule::drawString(int x, int y, const char* text, uint16_t color) {
    if (!driver || !text) return;
    #ifdef MRJ_DISPLAY_TFT
        Adafruit_GFX* t = (Adafruit_GFX*)driver;
        t->setCursor(x, y);
        t->setTextColor(color);
        t->print(text);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->setCursor(x, y);
            ((Adafruit_SSD1306*)driver)->setTextColor(color ? SSD1306_WHITE : SSD1306_BLACK);
            ((Adafruit_SSD1306*)driver)->print(text);
        #else
            U8G2* u = (U8G2*)driver;
            u->setFont(u8g2_font_6x10_tf);
            u->setDrawColor(color ? 1 : 0);
            u->drawStr(x, y + 10, text);  // U8G2 baseline is bottom-left
        #endif
    #endif
}

void DisplayModule::drawStringCenter(int y, const char* text, uint16_t color) {
    if (!driver || !text) return;
    #ifdef MRJ_DISPLAY_TFT
        Adafruit_GFX* t = (Adafruit_GFX*)driver;
        int16_t x1, y1;
        uint16_t w, h;
        t->setTextColor(color);
        t->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
        t->setCursor((width - w) / 2, y);
        t->print(text);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            int16_t x1, y1;
            uint16_t w, h;
            ((Adafruit_SSD1306*)driver)->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
            ((Adafruit_SSD1306*)driver)->setCursor((width - w) / 2, y);
            ((Adafruit_SSD1306*)driver)->setTextColor(color ? SSD1306_WHITE : SSD1306_BLACK);
            ((Adafruit_SSD1306*)driver)->print(text);
        #else
            U8G2* u = (U8G2*)driver;
            u->setFont(u8g2_font_6x10_tf);
            int tw = u->getStrWidth(text);
            u->setDrawColor(color ? 1 : 0);
            u->drawStr((width - tw) / 2, y + 10, text);
        #endif
    #endif
}

void DisplayModule::drawPixel(int x, int y, uint16_t color) {
    if (!driver) return;
    #ifdef MRJ_DISPLAY_TFT
        ((Adafruit_GFX*)driver)->drawPixel(x, y, color);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->drawPixel(x, y, color ? SSD1306_WHITE : SSD1306_BLACK);
        #else
            ((U8G2*)driver)->setDrawColor(color ? 1 : 0);
            ((U8G2*)driver)->drawPixel(x, y);
        #endif
    #endif
}

void DisplayModule::drawLine(int x1, int y1, int x2, int y2, uint16_t color) {
    if (!driver) return;
    #ifdef MRJ_DISPLAY_TFT
        ((Adafruit_GFX*)driver)->drawLine(x1, y1, x2, y2, color);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->drawLine(x1, y1, x2, y2, color ? SSD1306_WHITE : SSD1306_BLACK);
        #else
            ((U8G2*)driver)->setDrawColor(color ? 1 : 0);
            ((U8G2*)driver)->drawLine(x1, y1, x2, y2);
        #endif
    #endif
}

void DisplayModule::drawRect(int x, int y, int w, int h, uint16_t color) {
    if (!driver) return;
    #ifdef MRJ_DISPLAY_TFT
        ((Adafruit_GFX*)driver)->drawRect(x, y, w, h, color);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->drawRect(x, y, w, h, color ? SSD1306_WHITE : SSD1306_BLACK);
        #else
            ((U8G2*)driver)->setDrawColor(color ? 1 : 0);
            ((U8G2*)driver)->drawFrame(x, y, w, h);
        #endif
    #endif
}

void DisplayModule::fillRect(int x, int y, int w, int h, uint16_t color) {
    if (!driver) return;
    #ifdef MRJ_DISPLAY_TFT
        ((Adafruit_GFX*)driver)->fillRect(x, y, w, h, color);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->fillRect(x, y, w, h, color ? SSD1306_WHITE : SSD1306_BLACK);
        #else
            ((U8G2*)driver)->setDrawColor(color ? 1 : 0);
            ((U8G2*)driver)->drawBox(x, y, w, h);
        #endif
    #endif
}

void DisplayModule::drawBitmap(int x, int y, const uint8_t* bitmap, int w, int h, uint16_t color) {
    if (!driver || !bitmap) return;
    #ifdef MRJ_DISPLAY_TFT
        ((Adafruit_GFX*)driver)->drawBitmap(x, y, bitmap, w, h, color);
    #elif defined(MRJ_DISPLAY_OLED)
        #if MRJ_DISPLAY_TYPE == DISPLAY_TYPE_SSD1306
            ((Adafruit_SSD1306*)driver)->drawBitmap(x, y, bitmap, w, h, color ? SSD1306_WHITE : SSD1306_BLACK);
        #else
            ((U8G2*)driver)->setDrawColor(color ? 1 : 0);
            ((U8G2*)driver)->drawBitmap(x, y, w / 8, h, bitmap);
        #endif
    #endif
}

// ============================================================
// HIGH-LEVEL UI
// ============================================================
void DisplayModule::showSplash() {
    clear();
    drawStringCenter(30, "mrj v" FIRMWARE_VERSION, THEME_TEXT);
    update();
    delay(2000);
}

void DisplayModule::showStatus(const char* line1, const char* line2, const char* line3) {
    clear();
    drawString(0, 10, line1);
    if (strlen(line2) > 0) drawString(0, 30, line2);
    if (strlen(line3) > 0) drawString(0, 50, line3);
    update();
}

void DisplayModule::showIP(const char* ip) {
    drawString(0, height - 10, ip);
    update();
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
    update();
}
