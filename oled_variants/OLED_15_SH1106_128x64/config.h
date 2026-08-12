#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stddef.h>

#define FIRMWARE_NAME       "mrj firmware v2"
#define FIRMWARE_VERSION    "2.1.0"
#define FIRMWARE_AUTHOR     "mrj team"

#define DEFAULT_AP_SSID     "MRJ_AP"
#define DEFAULT_AP_PASS     ""
#define DEFAULT_WEB_PORT    80
#define DEFAULT_WEB_USER    "admin"
#define DEFAULT_WEB_PASS    "mrj12345"

#define DEFAULT_NETHERCAP_SSID  "MRJ_FreeWiFi"

#define EEPROM_SIZE         256
#define EEPROM_MAGIC_VALUE  0xAA55
#define EEPROM_VERSION_VALUE 2

#define MAX_STR_LEN         32
#define MAX_SCRIPT_SIZE     10240UL
#define MAX_FILENAME_LEN    64
#define MAX_UPLOAD_SIZE     (100UL * 1024UL * 1024UL)
#define RATE_LIMIT_REQUESTS 10
#define RATE_LIMIT_WINDOW   60000UL

#define DEAUTH_FRAME_DELAY  100

#define IR_BUFFER_SIZE      1024
#define SD_LOG_DIR          "/mrj_logs"
#define SD_CAPTURE_DIR      "/mrj_captures"
#define SD_CONFIG_DIR       "/mrj_config"
#define SD_PHISHING_DIR     "/phishing"
#define SD_SCRIPTS_DIR      "/scripts"

#define BUZZER_ENABLED_DEFAULT  true
#define BUZZER_VOLUME_DEFAULT   128
#define MENU_SCROLL_DELAY       150
#define SPLASH_DURATION         2000

#define OTA_HOSTNAME            "mrj_esp32"
#define OTA_PORT                3232

#define BT_TRANSFER_ENABLED     true
#define BT_DEVICE_NAME          "MRJ_V2_BT"

#define THEME_BG                0x0000
#define THEME_TEXT              0x001F

#define DISPLAY_TYPE_NONE       0
#define DISPLAY_TYPE_SSD1306    1
#define DISPLAY_TYPE_SH1106     2
#define DISPLAY_TYPE_SSD1309    3
#define DISPLAY_TYPE_SH1107     4
#define DISPLAY_TYPE_ST7735     5
#define DISPLAY_TYPE_ST7789     6
#define DISPLAY_TYPE_ILI9341    7
#define DISPLAY_TYPE_ILI9488    8
#define DISPLAY_TYPE_SSD1327    9

#define DISPLAY_BUS_I2C         0
#define DISPLAY_BUS_SPI         1

// ============================================================
// DISPLAY SELECTION — BUILD FLAGS
// ============================================================
#if defined(MRJ_DISPLAY_ST7735_18)
    // 1.8" ST7735 128x160
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ST7735
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  160
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ILI9341_24)
    // 2.4" ILI9341 240x320
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ILI9341
    #define MRJ_DISPLAY_WIDTH   240
    #define MRJ_DISPLAY_HEIGHT  320
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ILI9341_28)
    // 2.8" ILI9341 240x320
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ILI9341
    #define MRJ_DISPLAY_WIDTH   240
    #define MRJ_DISPLAY_HEIGHT  320
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ILI9488_35)
    // 3.5" ILI9488 320x480
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ILI9488
    #define MRJ_DISPLAY_WIDTH   320
    #define MRJ_DISPLAY_HEIGHT  480
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ST7789_13)
    // 1.3" ST7789 240x240 (square)
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ST7789
    #define MRJ_DISPLAY_WIDTH   240
    #define MRJ_DISPLAY_HEIGHT  240
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ST7789_154)
    // 1.54" ST7789 240x240 (square)
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ST7789
    #define MRJ_DISPLAY_WIDTH   240
    #define MRJ_DISPLAY_HEIGHT  240
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ST7789_20)
    // 2.0" ST7789 240x320
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ST7789
    #define MRJ_DISPLAY_WIDTH   240
    #define MRJ_DISPLAY_HEIGHT  320
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_ST7789_24)
    // 2.4" ST7789 240x320
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ST7789
    #define MRJ_DISPLAY_WIDTH   240
    #define MRJ_DISPLAY_HEIGHT  320
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT

#elif defined(MRJ_DISPLAY_SSD1306_096)
    // 0.96" SSD1306 128x64
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_SSD1306
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  64
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_I2C
    #define MRJ_DISPLAY_OLED
    #define MRJ_NO_TEAM_MUTEX

#elif defined(MRJ_DISPLAY_SSD1306_13)
    // 1.3" SSD1306 128x64
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_SSD1306
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  64
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_I2C
    #define MRJ_DISPLAY_OLED
    #define MRJ_NO_TEAM_MUTEX

#elif defined(MRJ_DISPLAY_SH1106_15)
    // 1.5" SH1106 128x64
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_SH1106
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  64
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_I2C
    #define MRJ_DISPLAY_OLED
    #define MRJ_NO_TEAM_MUTEX

#elif defined(MRJ_DISPLAY_SSD1306_20)
    // 2.0" SSD1306 128x64
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_SSD1306
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  64
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_I2C
    #define MRJ_DISPLAY_OLED
    #define MRJ_NO_TEAM_MUTEX

#elif defined(MRJ_DISPLAY_SH1106_242)
    // 2.42" SH1106 128x64
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_SH1106
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  64
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_I2C
    #define MRJ_DISPLAY_OLED
    #define MRJ_NO_TEAM_MUTEX

#elif defined(MRJ_DISPLAY_SSD1327)
    // SSD1327 128x128
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_SSD1327
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  128
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_I2C
    #define MRJ_DISPLAY_OLED
    #define MRJ_NO_TEAM_MUTEX

#else
    // Soft default for library detection (Arduino CLI / IDE without build flags)
    // Real build MUST pass -DMRJ_DISPLAY_XXXX via compile.sh or --build-property
    #define MRJ_DISPLAY_TYPE    DISPLAY_TYPE_ST7735
    #define MRJ_DISPLAY_WIDTH   128
    #define MRJ_DISPLAY_HEIGHT  160
    #define MRJ_DISPLAY_BUS     DISPLAY_BUS_SPI
    #define MRJ_DISPLAY_TFT
#endif

// ============================================================
// EEPROM LAYOUT
// ============================================================
#define EE_MAGIC                0
#define EE_VERSION              2
#define EE_CHECKSUM             3
#define EE_WEB_USER             4
#define EE_WEB_PASS             36
#define EE_AP_SSID              68
#define EE_AP_PASS              100
#define EE_FLAG_CONFIGURED      132
#define EE_AP_PASS_SET          133

#define EE_DISPLAY_TYPE         134
#define EE_DISPLAY_WIDTH        135
#define EE_DISPLAY_HEIGHT       136
#define EE_DISPLAY_ADDR         137
#define EE_DISPLAY_BUS          138
#define EE_DISPLAY_ROTATION     139
#define EE_DISPLAY_ENABLED      140

#define EE_MODULE_IR_RECV       141
#define EE_MODULE_IR_SEND       142
#define EE_MODULE_BADUSB        143
#define EE_MODULE_CC1101        144
#define EE_MODULE_RFID          145
#define EE_MODULE_NFC           146
#define EE_MODULE_IBUTTON       147
#define EE_MODULE_TOUCH         148

#define EE_WEB_COLOR            150
#define EE_DISPLAY_COLOR        154
#define EE_BG_COLOR             158

#define EE_NETHERCAP_SSID       162

#define EEPROM_LAYOUT_SIZE      194
static_assert(EEPROM_LAYOUT_SIZE <= EEPROM_SIZE, "EEPROM layout exceeds EEPROM_SIZE");

#define SUBGHZ_DEFAULT_FREQ     433.92f
#define SUBGHZ_MIN_FREQ         300.0f
#define SUBGHZ_MAX_FREQ         928.0f

#endif
