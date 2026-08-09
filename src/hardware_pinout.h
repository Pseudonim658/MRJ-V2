#ifndef HARDWARE_PINOUT_H
#define HARDWARE_PINOUT_H

#include <Arduino.h>

// ============================================================
// MRJ V2 — ST7735 TFT 1.77" 128x160
// TEAM PIN SHARING: Team A & Team B tidak aktif bersamaan,
// jadi pin-pin mereka bisa dibagi (pin reuse).
// ============================================================

// ========== CORE (Always Active) ==========
// BUTTONS
#define BTN_UP              32
#define BTN_DOWN            33
#define BTN_SELECT          25
#define BTN_BACK            34

// BUZZER
#define BUZZER_PIN          13
#define BUZZER_FREQ         2000
#define BUZZER_RES          8

// VSPI — SHARED (TFT + optional SPI devices)
#define VSPI_SCK            18
#define VSPI_MISO           19
#define VSPI_MOSI           23

// ST7735 TFT
#define DISPLAY_SCK         VSPI_SCK
#define DISPLAY_MISO        VSPI_MISO
#define DISPLAY_MOSI        VSPI_MOSI
#define DISPLAY_CS          5
#define DISPLAY_DC          21
#define DISPLAY_RST         22
#define DISPLAY_BL          -1

// SD CARD — HSPI (dedicated, tidak di-share)
#define HSPI_SCK            14
#define HSPI_MISO           26
#define HSPI_MOSI           27
#define SD_CS               4

// NFC — I2C (Team B, tapi IRQ bisa share karena input-only)
#define NFC_SDA             16
#define NFC_SCL             17
#define NFC_IRQ             35

// IR (Always ON)
#define IR_RECV_PIN         36
#define IR_SEND_PIN         12

// IBUTTON
#define IBUTTON_PIN         2

// BATTERY ADC
#define ADC_BATTERY_PIN     37

// ========== SHARED PINS (Team A/B Reuse) ==========
// Karena Team A dan Team B tidak aktif bersamaan,
// pin-pin berikut dipakai bergantian oleh kedua team.

// Shared SPI CS: CC1101 (Team A) / RFID-MFRC522 (Team B)
#define SHARED_SPI_CS       0

// Shared Control Pin: CC1101_GDO0 (Team A, input) / RFID_RST (Team B, output)
#define SHARED_CTRL_PIN     3

// Shared UART: CH9326 (Team A) / RFID125 (Team B)
// RX pakai pin input-only (aman), TX pakai pin output
#define SHARED_UART_TX      15
#define SHARED_UART_RX      39   // Input-only, aman untuk RX

// ========== TEAM A MAPPING ==========
#define CC1101_CS           SHARED_SPI_CS
#define CC1101_GDO0         SHARED_CTRL_PIN
#define CC1101_GDO2         -1   // Tidak digunakan (pin hemat)

#define CH9326_TX           SHARED_UART_TX
#define CH9326_RX           SHARED_UART_RX

// ========== TEAM B MAPPING ==========
#define RFID_CS             SHARED_SPI_CS
#define RFID_RST            SHARED_CTRL_PIN

#define RFID125_TX          SHARED_UART_TX
#define RFID125_RX          SHARED_UART_RX

// ========== TOUCH (Disabled) ==========
#define TOUCH_CS            -1
#define TOUCH_IRQ           -1

// ========== NEOPIXEL (Disabled) ==========
#define NEOPIXEL_PIN        -1

#endif
