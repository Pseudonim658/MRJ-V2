# 💀 MRJ V2 — Modular Research Jack

> **Universal ESP32 Display Firmware & Modular Hardware Toolkit**

![MRJ V2](mrj%20v2.png)

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif)](https://www.espressif.com/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino)](https://www.arduino.cc/)
[![Build](https://img.shields.io/badge/Build-PlatformIO-orange?style=for-the-badge&logo=platformio)](https://platformio.org/)
[![Displays](https://img.shields.io/badge/Displays-14-green?style=for-the-badge)](https://github.com/Pseudonim658/MRJ-V2)
[![GitHub Release](https://img.shields.io/github/v/release/Pseudonim658/MRJ-V2?style=for-the-badge&logo=github)](https://github.com/Pseudonim658/MRJ-V2/releases)
[![License](https://img.shields.io/github/license/Pseudonim658/MRJ-V2?style=for-the-badge&logo=github)](https://github.com/Pseudonim658/MRJ-V2)

**ESP32 • C++ • Arduino • PlatformIO • 14 Display Variants • Modular Hardware**

---

## 📑 Table of Contents

- [📊 Project Overview](#-project-overview)
- [✨ Features](#-features)
- [🖥️ Display Support](#️-display-support)
- [🔌 ESP32 Pinout](#-esp32-pinout)
- [📺 TFT Pinout](#-tft-pinout)
- [🟦 OLED Pinout](#-oled-pinout)
- [📡 Hardware Modules](#-hardware-modules)
- [🎮 Controls](#-controls)
- [🔀 TFT SPI Architecture](#-tft-spi-architecture)
- [🟦 OLED Architecture](#-oled-architecture)
- [📚 Libraries](#-libraries)
- [⚙️ Display Build Flags](#️-display-build-flags)
- [🛠️ PlatformIO](#️-platformio)
- [📁 Project Structure](#-project-structure)
- [🧩 Firmware Architecture](#-firmware-architecture)
- [⚡ Power](#-power)
- [⚠️ Hardware Notes](#️-hardware-notes)
- [🔐 Responsible Use](#-responsible-use)
- [📦 Firmware Releases](#-firmware-releases)
- [👥 MRJ V2 Team](#-mrj-v2-team)

---

# 📊 Project Overview

| Category | Details |
|---|---|
| Project | MRJ V2 |
| Full Name | Modular Research Jack |
| MCU | ESP32 DevKit V1 |
| CPU | 240 MHz |
| Flash | 4 MB |
| Displays | 14 variants |
| TFT | 9 variants |
| OLED | 5 variants |
| Language | C++ |
| Framework | Arduino |
| Build System | PlatformIO |
| Firmware | `.bin` |
| Source | `.cpp` / `.h` / `.ino` |

---

# ✨ Features

| Feature | Support |
|---|:---:|
| ESP32 DevKit V1 | ✅ |
| Universal Display Support | ✅ |
| 14 Display Variants | ✅ |
| TFT Displays | ✅ |
| OLED Displays | ✅ |
| SD Card | ✅ |
| NFC / PN532 | ✅ |
| RFID / MFRC522 | ✅ |
| Sub-GHz / CC1101 | ✅ |
| IR Receiver | ✅ |
| IR Transmitter | ✅ |
| iButton / DS1990 | ✅ |
| Buzzer | ✅ |
| 4 Navigation Buttons | ✅ |
| Battery Monitoring | ✅ |
| Web Interface | 🔧 |
| OTA Update | 🔧 |
| Modular Architecture | ✅ |

---

# 🖥️ Display Support

MRJ V2 supports **14 display variants**.

## TFT Displays

| No. | Size | Driver | Resolution | Interface |
|---:|---|---|---:|---|
| 1 | 1.77" | ST7735S | 128×160 | SPI |
| 2 | 1.8" | ST7735 | 128×160 | SPI |
| 3 | 1.3" | ST7789 | 240×240 | SPI |
| 4 | 1.54" | ST7789 | 240×240 | SPI |
| 5 | 2.0" | ST7789 | 240×320 | SPI |
| 6 | 2.4" | ST7789 | 240×320 | SPI |
| 7 | 2.4" | ILI9341 | 240×320 | SPI |
| 8 | 2.8" | ILI9341 | 240×320 | SPI |
| 9 | 3.5" | ILI9488 | 320×480 | SPI |

## OLED Displays

| No. | Size | Driver | Resolution | Interface |
|---:|---|---|---:|---|
| 10 | 0.96" | SSD1306 | 128×64 | I2C |
| 11 | 1.3" | SSD1306 | 128×64 | I2C |
| 12 | 1.5" | SH1106 | 128×64 | I2C |
| 13 | 2.0" | SSD1306 | 128×64 | I2C |
| 14 | 2.42" | SH1106 | 128×64 | I2C |

---

# 🔌 ESP32 Pinout

MRJ V2 menggunakan konfigurasi pin hardware tetap.

## Fixed Hardware Pinout

| Function | GPIO | Direction |
|---|---:|---|
| SD SCK | `14` | Output |
| SD MISO | `26` | Input |
| SD MOSI | `27` | Output |
| SD CS | `4` | Output |
| I2C SDA | `16` | Bidirectional |
| I2C SCL | `17` | Output |
| IR Receiver | `36` | Input |
| IR Transmitter | `12` | Output |
| iButton / DS1990 | `2` | Bidirectional |
| Buzzer | `13` | Output |
| Button UP | `32` | Input |
| Button DOWN | `33` | Input |
| Button SELECT | `25` | Input |
| Button BACK | `34` | Input |

---

# 📺 TFT Pinout

```text
TFT
│
├── VCC  → 3.3V
├── GND  → GND
├── SCK  → GPIO 18
├── MISO → GPIO 19
├── MOSI → GPIO 23
├── CS   → GPIO 5
├── DC   → GPIO 21
├── RST  → GPIO 22
└── BL   → 3.3V / NC
TFT Pin
ESP32
SCK
GPIO 18
MISO
GPIO 19
MOSI
GPIO 23
CS
GPIO 5
DC
GPIO 21
RST
GPIO 22
🟦 OLED Pinout
OLED
│
├── VCC → 3.3V
├── GND → GND
├── SDA → GPIO 16
└── SCL → GPIO 17
I2C Addresses
OLED  → 0x3C
PN532 → 0x24
OLED dan PN532 menggunakan bus I2C yang sama dengan alamat berbeda.
📡 Hardware Modules
MicroSD / SD Card
SCK  → GPIO 14
MISO → GPIO 26
MOSI → GPIO 27
CS   → GPIO 4
Interface:
SPI / HSPI
Sub-GHz — CC1101
CS → GPIO 5
RFID — MFRC522
CS  → GPIO 15
RST → GPIO 21
NFC — PN532
SDA → GPIO 16
SCL → GPIO 17
I2C Address → 0x24
IR
IR Receiver → GPIO 36
IR LED      → GPIO 12
iButton
DS1990 / iButton → GPIO 2
Buzzer
Buzzer → GPIO 13
🎮 Controls
MRJ V2 menggunakan empat tombol navigasi.
        ┌─────────┐
        │   UP    │
        ├─────────┤
        │  DOWN   │
        ├─────────┤
        │ SELECT  │
        ├─────────┤
        │  BACK   │
        └─────────┘
Button
GPIO
UP
32
DOWN
33
SELECT
25
BACK
34
🔀 TFT SPI Architecture
TFT menggunakan bus VSPI ESP32.
             VSPI
              │
       ┌──────┼──────┐
       │      │      │
      TFT   CC1101  MFRC522
       │      │      │
       └──────┴──────┘
          Shared SPI
Chip Select harus dikelola dengan benar agar perangkat SPI tidak aktif secara bersamaan pada saat yang sama.
🟦 OLED Architecture
OLED menggunakan I2C sehingga VSPI tetap tersedia untuk perangkat SPI lainnya.
             ESP32
               │
       ┌───────┼────────┐
       │       │        │
      OLED    PN532   SPI Modules
       │       │        │
       └── I2C ┘        └── VSPI
📚 Libraries
Core
bblanchon/ArduinoJson
me-no-dev/AsyncTCP
me-no-dev/ESP Async WebServer
DNSServer
TFT
adafruit/Adafruit ST7735 and ST7789 Library
adafruit/Adafruit ILI9341
adafruit/Adafruit GFX Library
OLED
adafruit/Adafruit SSD1306
adafruit/Adafruit GFX Library
olikraus/U8g2
⚙️ Display Build Flags
TFT
MRJ_DISPLAY_ST7735S_177
MRJ_DISPLAY_ST7735_18
MRJ_DISPLAY_ST7789_13
MRJ_DISPLAY_ST7789_154
MRJ_DISPLAY_ST7789_20
MRJ_DISPLAY_ST7789_24
MRJ_DISPLAY_ILI9341_24
MRJ_DISPLAY_ILI9341_28
MRJ_DISPLAY_ILI9488_35
OLED
MRJ_DISPLAY_SSD1306_096
MRJ_DISPLAY_SSD1306_13
MRJ_DISPLAY_SH1106_15
MRJ_DISPLAY_SSD1306_20
MRJ_DISPLAY_SH1106_242
🛠️ PlatformIO
MRJ V2 dikembangkan menggunakan C++, Arduino Framework, dan PlatformIO.
Contoh konfigurasi OLED 0.96" SSD1306:
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200
upload_speed = 921600

board_build.f_cpu = 240000000L

build_flags =
    -DMRJ_DISPLAY_SSD1306_096
    -DMRJ_DISPLAY_WIDTH=128
    -DMRJ_DISPLAY_HEIGHT=64

lib_deps =
    bblanchon/ArduinoJson
    adafruit/Adafruit SSD1306
    adafruit/Adafruit GFX Library
    olikraus/U8g2
Build
pio run
Upload
pio run -t upload
Serial Monitor
pio device monitor
📁 Project Structure
mrj_fw_v2/
│
├── platformio.ini
│
├── src/
│   ├── MRJ_FW_V2.ino
│   ├── config.h
│   ├── hardware_pinout.h
│   ├── display.h
│   ├── display.cpp
│   ├── reserved_pins.h
│   ├── reserved_pins.cpp
│   ├── eeprom_manager.h
│   ├── eeprom_manager.cpp
│   ├── buzzer.h
│   ├── buzzer.cpp
│   ├── sd_card.h
│   ├── sd_card.cpp
│   ├── logger.h
│   ├── logger.cpp
│   ├── web_server.h
│   ├── web_server.cpp
│   ├── subghz.h
│   ├── subghz.cpp
│   ├── nfc_module.h
│   ├── nfc_module.cpp
│   ├── rfid_module.h
│   ├── rfid_module.cpp
│   ├── rfid_125khz.h
│   ├── rfid_125khz.cpp
│   ├── ibutton.h
│   ├── ibutton.cpp
│   ├── ir_remote.h
│   ├── ir_remote.cpp
│   ├── ir_decoder.h
│   ├── ir_decoder.cpp
│   ├── ch9326.h
│   ├── ch9326.cpp
│   ├── gpio_control.h
│   ├── gpio_control.cpp
│   ├── ota_update.h
│   ├── ota_update.cpp
│   ├── menu.h
│   └── menu.cpp
│
├── data/
│   └── index.html
│
└── README.md
🧩 Firmware Architecture
                    ┌────────────────────┐
                    │      MRJ V2        │
                    │ Modular Research   │
                    │       Jack         │
                    └─────────┬──────────┘
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
     DISPLAY               INPUT                STORAGE
        │                     │                     │
   ┌────┴────┐          ┌─────┴─────┐             SD
   │         │          │           │
  TFT      OLED       Buttons     GPIO
   │         │
  SPI       I2C
        │
        ├──────── NFC
        ├──────── RFID
        ├──────── CC1101
        ├──────── IR
        └──────── iButton
⚡ Power
MRJ V2 menggunakan lingkungan logika 3.3V.
⚠️ Selalu periksa tegangan kerja setiap modul sebelum melakukan wiring.
Jangan menganggap breakout board aman untuk 3.3V hanya karena IC di dalamnya menggunakan logika 3.3V.
⚠️ Hardware Notes
Verify your exact ESP32 DevKit V1 pinout before wiring.
GPIO34–39 are input-only on classic ESP32.
GPIO34 does not provide an internal pull-up.
GPIO36/39 are input-only.
Jangan memberi beban arus besar langsung dari GPIO ESP32.
Gunakan level shifting jika diperlukan.
Periksa konflik SPI sebelum mengaktifkan beberapa perangkat.
Pastikan alamat I2C tidak bentrok.
Gunakan common ground untuk seluruh modul.
🔐 Responsible Use
MRJ V2 ditujukan untuk:
Electronics learning
Hardware experimentation
RF research
Device diagnostics
Firmware development
Authorized testing
Perangkat milik sendiri
Gunakan antarmuka wireless, RFID/NFC, IR, HID, dan hardware lainnya hanya pada perangkat yang kamu miliki atau yang telah memberikan izin untuk diuji.
📦 Firmware Releases
Firmware binary dapat didistribusikan melalui GitHub Releases.
MRJ V2 Release
│
├── mrj_fw_v2.bin
├── mrj_fw_v2_bootloader.bin
└── mrj_fw_v2_partitions.bin
👥 MRJ V2 Team
MRJ V2 Team
MRJ — Modular Research Jack
Build • Learn • Experiment
�

💀 MRJ V2
Modular Research Jack
ESP32 • Hardware Research • Firmware Development • Modular Design
�⁠�
�⁠�
�


Build • Learn • Experiment
MRJ V2 — Modular ESP32 Hardware Platform
�
```
