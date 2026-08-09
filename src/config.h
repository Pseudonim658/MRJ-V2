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

#define DISPLAY_BUS_I2C         0
#define DISPLAY_BUS_SPI         1

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
