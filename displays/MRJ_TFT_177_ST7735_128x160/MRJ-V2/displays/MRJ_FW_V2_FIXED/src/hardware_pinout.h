#ifndef HARDWARE_PINOUT_H
#define HARDWARE_PINOUT_H

#include <Arduino.h>
#include "config.h"

// ============================================================
// MRJ V2 — ST7735 TFT 1.77" 128x160
// SINGLE DISPLAY — ALL CORE MODULES ACTIVE
// CONFLICT-FREE PINOUT
// ============================================================

// BUTTONS
#define BTN_UP              32
#define BTN_DOWN            33
#define BTN_SELECT          25
#define BTN_BACK            34

// BUZZER
#define BUZZER_PIN          13
#define BUZZER_FREQ         2000
#define BUZZER_RES          8

// VSPI — SHARED (TFT, CC1101, RFID)
#define VSPI_SCK            18
#define VSPI_MISO           19
#define VSPI_MOSI           23

// ST7735 TFT
#define DISPLAY_SCK         18
#define DISPLAY_MISO        19
#define DISPLAY_MOSI        23
#define DISPLAY_CS          5
#define DISPLAY_DC          21
#define DISPLAY_RST         22
#define DISPLAY_BL          -1

// SD CARD — HSPI
#define HSPI_SCK            14
#define HSPI_MISO           26
#define HSPI_MOSI           27
#define SD_CS               4

// NFC — I2C
#define NFC_SDA             16
#define NFC_SCL             17
#define NFC_IRQ             35

// IR
#define IR_RECV_PIN         36
#define IR_SEND_PIN         12

// IBUTTON
#define IBUTTON_PIN         2

// BATTERY ADC
#define ADC_BATTERY_PIN     37

// CC1101 — DISABLED (aktif melalui Module Control)
#define CC1101_CS           -1
#define CC1101_GDO0         -1
#define CC1101_GDO2         -1

// RFID — DISABLED (aktif melalui Module Control)
#define RFID_CS             -1
#define RFID_RST            -1

// CH9326 / BadUSB — DISABLED (aktif melalui Module Control)
#define CH9326_TX           -1
#define CH9326_RX           -1

// RFID 125kHz — DISABLED (conflict dengan NFC I2C jika aktif)
#define RFID125_RX          -1
#define RFID125_TX          -1

// TOUCH — DISABLED
#define TOUCH_CS            -1
#define TOUCH_IRQ           -1

// NEOPIXEL
#define NEOPIXEL_PIN        -1

#endif