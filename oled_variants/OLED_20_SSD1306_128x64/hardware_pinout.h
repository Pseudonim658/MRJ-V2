#ifndef HARDWARE_PINOUT_H
#define HARDWARE_PINOUT_H

#include <Arduino.h>
#include "config.h"

// ============================================================
// MRJ V2 — UNIVERSAL PINOUT (TFT vs OLED)
// ============================================================

// BUTTONS (fixed)
#define BTN_UP              32
#define BTN_DOWN            33
#define BTN_SELECT          25
#define BTN_BACK            34

// BUZZER
#define BUZZER_PIN          13
#define BUZZER_FREQ         2000
#define BUZZER_RES          8

// SD CARD — HSPI (fixed)
#define HSPI_SCK            14
#define HSPI_MISO           26
#define HSPI_MOSI           27
#define SD_CS               4

// IR (fixed)
#define IR_RECV_PIN         36
#define IR_SEND_PIN         12

// IBUTTON (fixed)
#define IBUTTON_PIN         2

// BATTERY ADC (fixed)
#define ADC_BATTERY_PIN     37

// NEOPIXEL (optional)
#define NEOPIXEL_PIN        -1

// ============================================================
// DISPLAY & MODULE PINOUT — TFT vs OLED
// ============================================================
#ifdef MRJ_DISPLAY_TFT
    // TFT uses VSPI (pins 18/19/23) — shared with CC1101/RFID
    // Team A/B mutual exclusion REQUIRED
    #define VSPI_SCK            18
    #define VSPI_MISO           19
    #define VSPI_MOSI           23

    #define DISPLAY_SCK         18
    #define DISPLAY_MISO        19
    #define DISPLAY_MOSI        23
    #define DISPLAY_CS          5
    #define DISPLAY_DC          21
    #define DISPLAY_RST         22
    #define DISPLAY_BL          -1

    // CC1101 — DISABLED by default (enable via Module Control, Team A)
    #define CC1101_CS           -1
    #define CC1101_GDO0         -1
    #define CC1101_GDO2         -1

    // RFID 13.56MHz — DISABLED by default (enable via Module Control, Team B)
    #define RFID_CS             -1
    #define RFID_RST            -1

    // CH9326 / BadUSB — DISABLED by default (enable via Module Control, Team A)
    #define CH9326_TX           -1
    #define CH9326_RX           -1

    // RFID 125kHz — DISABLED (conflict potential)
    #define RFID125_RX          -1
    #define RFID125_TX          -1

    // TOUCH — DISABLED
    #define TOUCH_CS            -1
    #define TOUCH_IRQ           -1

    // NFC — I2C (always available)
    #define NFC_SDA             16
    #define NFC_SCL             17
    #define NFC_IRQ             35

#elif defined(MRJ_DISPLAY_OLED)
    // OLED uses I2C (shared with NFC) — frees VSPI for all modules
    // NO Team A/B mutual exclusion — all modules can be enabled together
    #define DISPLAY_SDA         16
    #define DISPLAY_SCL         17
    #define DISPLAY_RST         -1
    #define DISPLAY_I2C_ADDR    0x3C

    // VSPI — FREE for CC1101 + RFID simultaneously
    #define VSPI_SCK            18
    #define VSPI_MISO           19
    #define VSPI_MOSI           23

    // CC1101 — ENABLED via Module Control (CS=5)
    #define CC1101_CS           5
    #define CC1101_GDO0         -1
    #define CC1101_GDO2         -1

    // RFID 13.56MHz — ENABLED via Module Control (CS=15, RST=21)
    #define RFID_CS             15
    #define RFID_RST            21

    // CH9326 / BadUSB — ENABLED via Module Control (UART2 remapped)
    #define CH9326_TX           22
    #define CH9326_RX           35   // GPIO35 is input-only, OK for RX

    // RFID 125kHz — optional on UART1 or bit-bang
    #define RFID125_RX          39   // GPIO39 input-only, OK for RX
    #define RFID125_TX          -1

    // TOUCH — DISABLED
    #define TOUCH_CS            -1
    #define TOUCH_IRQ           -1

    // NFC — I2C shared with OLED (PN532 addr 0x24, OLED addr 0x3C)
    #define NFC_SDA             16
    #define NFC_SCL             17
    #define NFC_IRQ             -1   // Optional, set to 35 if wired

#else
    // Default fallback (library detection / no display flag)
    #define VSPI_SCK            18
    #define VSPI_MISO           19
    #define VSPI_MOSI           23
    #define DISPLAY_CS          5
    #define DISPLAY_DC          21
    #define DISPLAY_RST         22
    #define DISPLAY_SDA         16
    #define DISPLAY_SCL         17
    #define DISPLAY_I2C_ADDR    0x3C
    #define CC1101_CS           -1
    #define CC1101_GDO0         -1
    #define CC1101_GDO2         -1
    #define RFID_CS             -1
    #define RFID_RST            -1
    #define CH9326_TX           -1
    #define CH9326_RX           -1
    #define RFID125_RX          -1
    #define RFID125_TX          -1
    #define TOUCH_CS            -1
    #define TOUCH_IRQ           -1
    #define NFC_SDA             16
    #define NFC_SCL             17
    #define NFC_IRQ             -1
#endif


#endif
