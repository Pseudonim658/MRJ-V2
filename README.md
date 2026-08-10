# 💀 MRJ V2 — Modular Research Jack

> **Universal ESP32 Display Firmware & Modular Hardware Toolkit**

<p align="center">
  <img src="mrj%20v2.png" alt="MRJ V2" width="420">
</p>

<p align="center">

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif)](https://www.espressif.com/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino)](https://www.arduino.cc/)
[![Build](https://img.shields.io/badge/Build-PlatformIO-orange?style=for-the-badge&logo=platformio)](https://platformio.org/)
[![Displays](https://img.shields.io/badge/Displays-14-green?style=for-the-badge)](https://github.com/Pseudonim658/MRJ-V2)
[![Release](https://img.shields.io/github/v/release/Pseudonim658/MRJ-V2?style=for-the-badge&logo=github)](https://github.com/Pseudonim658/MRJ-V2/releases)

</p>

---

## 📋 Overview

**MRJ V2 (Modular Research Jack)** is an ESP32-based modular hardware and firmware platform for electronics research, experimentation, diagnostics, development, and authorized security testing.

The project supports **14 display variants**, including TFT and OLED modules, with a modular hardware architecture for SD, IR, iButton, NFC, RFID, Sub-GHz, HID interfaces, GPIO, and other peripherals.

---

## ✨ Features

| Feature | Status |
|---|:---:|
| ESP32 DevKit V1 | ✅ |
| 14 Display Variants | ✅ |
| TFT Display Support | ✅ |
| OLED Display Support | ✅ |
| MicroSD / SD Card | ✅ |
| PN532 NFC | ✅ |
| MFRC522 RFID | ✅ |
| CC1101 Sub-GHz Interface | ✅ |
| IR Receiver | ✅ |
| IR Transmitter | ✅ |
| iButton / DS1990 | ✅ |
| Active Buzzer | ✅ |
| 4 Navigation Buttons | ✅ |
| Battery Monitoring | ✅ |
| Web Interface | 🔧 |
| OTA Update | 🔧 |
| Modular Firmware | ✅ |

---

# 🖥️ Display Support

MRJ V2 supports **14 display variants**.

## TFT Displays

| # | Display | Driver | Resolution | Interface |
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

| # | Display | Driver | Resolution | Interface |
|---:|---|---|---:|---|
| 10 | 0.96" | SSD1306 | 128×64 | I2C |
| 11 | 1.3" | SSD1306 | 128×64 | I2C |
| 12 | 1.5" | SH1106 | 128×64 | I2C |
| 13 | 2.0" | SSD1306 | 128×64 | I2C |
| 14 | 2.42" | SH1106 | 128×64 | I2C |

---

# 🔌 ESP32 Pinout

## Fixed Hardware Pins

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
| iButton | `2` | Bidirectional |
| Buzzer | `13` | Output |
| Button UP | `32` | Input |
| Button DOWN | `33` | Input |
| Button SELECT | `25` | Input |
| Button BACK | `34` | Input |

---

# 📺 TFT Pinout

```text
ESP32 DevKit V1
│
├── GPIO 18 ───── SCK
├── GPIO 19 ───── MISO
├── GPIO 23 ───── MOSI
├── GPIO 5  ───── CS
├── GPIO 21 ───── DC
└── GPIO 22 ───── RST

TFT POWER
├── VCC ───────── 3.3V
├── GND ───────── GND
└── BL  ───────── 3.3V / NC
```

🟦 OLED Pinout

```text
ESP32 DevKit V1
│
├── GPIO 16 ───── SDA
└── GPIO 17 ───── SCL

OLED POWER
├── VCC ───────── 3.3V
└── GND ───────── GND

I2C Addresses
OLED  → 0x3C
PN532 → 0x24
```

🎮 4-Button Controls

MRJ V2 menggunakan 4 tombol fisik.

```text
       ┌─────────────┐
       │     UP      │
       ├─────────────┤
       │    DOWN     │
       ├─────────────┤
       │   SELECT    │
       ├─────────────┤
       │    BACK     │
       └─────────────┘
```

Button GPIO Function
UP 32 Navigate Up
DOWN 33 Navigate Down
SELECT 25 Select / Enter
BACK 34 Back / Exit

📡 Hardware Modules

MicroSD

· SCK  → GPIO 14
· MISO → GPIO 26
· MOSI → GPIO 27
· CS   → GPIO 4
· Interface: SPI / HSPI

PN532 NFC

· SDA → GPIO 16
· SCL → GPIO 17
· I2C → 0x24

MFRC522 RFID

· CS  → GPIO 15
· RST → GPIO 21

CC1101

· CS → GPIO 5

IR Receiver

· VS1838B → GPIO 36

IR Transmitter

· 940nm IR LED → GPIO 12

iButton

· DS1990 → GPIO 2

Buzzer

· Active Buzzer → GPIO 13

---

📚 Programming & Libraries

· Programming Language: C++
· Framework: Arduino Framework
· Build System: PlatformIO

Core Libraries

· bblanchon/ArduinoJson
· me-no-dev/AsyncTCP
· me-no-dev/ESP Async WebServer
· DNSServer

TFT Libraries

· adafruit/Adafruit ST7735 and ST7789 Library
· adafruit/Adafruit ILI9341
· adafruit/Adafruit GFX Library

OLED Libraries

· adafruit/Adafruit SSD1306
· adafruit/Adafruit GFX Library
· olikraus/U8g2

---

⚙️ Display Build Flags

TFT

· MRJ_DISPLAY_ST7735S_177
· MRJ_DISPLAY_ST7735_18
· MRJ_DISPLAY_ST7789_13
· MRJ_DISPLAY_ST7789_154
· MRJ_DISPLAY_ST7789_20
· MRJ_DISPLAY_ST7789_24
· MRJ_DISPLAY_ILI9341_24
· MRJ_DISPLAY_ILI9341_28
· MRJ_DISPLAY_ILI9488_35

OLED

· MRJ_DISPLAY_SSD1306_096
· MRJ_DISPLAY_SSD1306_13
· MRJ_DISPLAY_SH1106_15
· MRJ_DISPLAY_SSD1306_20
· MRJ_DISPLAY_SH1106_242

---

🛠️ PlatformIO

Example TFT 1.77" ST7735S:

```ini
[env:esp32dev]

platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200
upload_speed = 921600

board_build.f_cpu = 240000000L

build_flags =
    -DMRJ_DISPLAY_ST7735S_177
    -DMRJ_DISPLAY_WIDTH=128
    -DMRJ_DISPLAY_HEIGHT=160

lib_deps =
    bblanchon/ArduinoJson
    me-no-dev/AsyncTCP
    me-no-dev/ESP Async WebServer
    DNSServer
    adafruit/Adafruit ST7735 and ST7789 Library
    adafruit/Adafruit GFX Library
```

Build

```bash
pio run
```

Upload

```bash
pio run -t upload
```

Serial Monitor

```bash
pio device monitor
```

---

📁 Project Structure

```text
mrj_fw_v2/
│
├── platformio.ini
│
├── src/
│   ├── MRJ_FW_V2.ino
│   ├── config.h
│   ├── hardware_pinout.h
│   │
│   ├── display.h
│   ├── display.cpp
│   │
│   ├── reserved_pins.h
│   ├── reserved_pins.cpp
│   │
│   ├── eeprom_manager.h
│   ├── eeprom_manager.cpp
│   │
│   ├── buzzer.h
│   ├── buzzer.cpp
│   │
│   ├── sd_card.h
│   ├── sd_card.cpp
│   │
│   ├── logger.h
│   ├── logger.cpp
│   │
│   ├── web_server.h
│   ├── web_server.cpp
│   │
│   ├── subghz.h
│   ├── subghz.cpp
│   │
│   ├── nfc_module.h
│   ├── nfc_module.cpp
│   │
│   ├── rfid_module.h
│   ├── rfid_module.cpp
│   │
│   ├── rfid_125khz.h
│   ├── rfid_125khz.cpp
│   │
│   ├── ibutton.h
│   ├── ibutton.cpp
│   │
│   ├── ir_remote.h
│   ├── ir_remote.cpp
│   │
│   ├── ir_decoder.h
│   ├── ir_decoder.cpp
│   │
│   ├── badusb.h
│   ├── badusb.cpp
│   │
│   ├── ch9326.h
│   ├── ch9326.cpp
│   │
│   ├── gpio_control.h
│   ├── gpio_control.cpp
│   │
│   ├── ota_update.h
│   ├── ota_update.cpp
│   │
│   ├── menu.h
│   └── menu.cpp
│
├── data/
│   └── index.html
│
└── README.md
```

---

🧩 Firmware Architecture

```text
                         ┌───────────────────┐
                         │      MRJ V2       │
                         │ Modular Research  │
                         │       Jack        │
                         └─────────┬─────────┘
                                   │
             ┌─────────────────────┼─────────────────────┐
             │                     │                     │
          DISPLAY                 INPUT                MODULES
             │                     │                     │
       ┌─────┴─────┐          ┌────┴────┐       ┌──────┴──────┐
       │           │          │         │       │             │
      TFT         OLED      Buttons    GPIO    RF/NFC        IR
       │           │
      SPI         I2C
       │           │
       └──────┬────┘
              │
        Display Manager
              │
        ┌─────┴─────┐
        │           │
      Menu       Hardware
        │           │
        └─────┬─────┘
             │
          ESP32 Core
```

---

⚡ Power

MRJ V2 menggunakan sistem logika 3.3V.

Component Typical Voltage
ESP32 3.3V / 5V USB
TFT 3.3V
OLED 3.3V
CC1101 3.3V
PN532 3.3V
MFRC522 3.3V
SD Module Check module
IR Receiver Check module

⚠️ Selalu periksa spesifikasi modul sebelum menghubungkannya ke ESP32.

---

⚠️ Hardware Notes

· GPIO 34–39 pada ESP32 klasik adalah input-only.
· GPIO34 tidak memiliki internal pull-up.
· GPIO36 digunakan sebagai input IR.
· GPIO39 dapat digunakan sebagai input-only untuk modul yang sesuai.
· Jangan memberi beban arus besar langsung dari GPIO ESP32.
· Gunakan level shifter jika diperlukan.
· Pastikan seluruh perangkat memiliki common GND.
· Periksa konflik pin sebelum melakukan wiring.
· Periksa alamat I2C sebelum menghubungkan perangkat I2C.

---

🔐 Responsible Use

MRJ V2 dibuat untuk:

· Electronics research
· Hardware experimentation
· Firmware development
· Device diagnostics
· RF research
· Learning
· Authorized security testing

Gunakan perangkat hanya pada hardware yang kamu miliki atau yang kamu memiliki izin untuk uji.

---

📦 Firmware Releases

Firmware tersedia melalui GitHub Releases.

```text
MRJ V2 Firmware
│
├── mrj_fw_v2.bin
├── mrj_fw_v2_bootloader.bin
└── mrj_fw_v2_partitions.bin
```

---

💀 MRJ V2 — Modular Research Jack
Build • Learn • Experiment
