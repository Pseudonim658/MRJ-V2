<div align="center">

# 🟢 MRJ V2

### ESP32 Security & Electronics Toolkit

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-orange?style=for-the-badge&logo=platformio)](https://platformio.org/)
[![ESP32](https://img.shields.io/badge/Board-ESP32%20DevKit%20V1-blue?style=for-the-badge&logo=espressif)](https://www.espressif.com/)
[![Display](https://img.shields.io/badge/Display-ST7735%20128%C3%97160-green?style=for-the-badge)](https://github.com/)
[![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-lightgrey?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![License](https://img.shields.io/badge/Use-Educational-yellow?style=for-the-badge)](https://github.com/)

**MRJ V2 Team • ESP32 Firmware Project • Educational & Authorized Testing**

</div>

<p align="center">
  <img src="mrj v2.png" alt="MRJ V2 Pinout and Wiring Guide" width="720">
</p>

<div align="center">

> **MRJ V2** is an ESP32-based electronics and security-testing toolkit designed for learning, hardware experimentation, and authorized testing on equipment you own or have permission to test.

</div>

## MRJ — Modular Research Jack

> **Multi-Function ESP32 Hardware Toolkit**

MRJ (Modular Research Jack) is a modular ESP32-based hardware toolkit designed for electronics research, experimentation, development, and learning.

## ✨ Overview

MRJ V2 is a modular firmware project for **ESP32 DevKit V1 (30-pin)**.

The project combines:

- 🖥️ **ST7735 TFT display**
- 🎮 **4-button menu interface**
- 💾 **SD card storage**
- 📡 **Sub-GHz module support**
- 📶 **Wi-Fi tools**
- 🔵 **Bluetooth/BLE tools**
- 📳 **NFC / RFID interfaces**
- 🔑 **iButton / Dallas reader**
- 🔴 **Infrared receiver/transmitter**
- ⌨️ **USB/HID-related hardware interfaces**
- 🔌 **GPIO control**
- 🌐 **Web interface**
- ⚙️ **Configuration and EEPROM management**
- 📝 **Logging**
- 🔄 **OTA update framework**

## 🖥️ Display Interface

The firmware is designed around a:

| Specification | Value |
|---|---|
| Driver | **ST7735** |
| Resolution | **128 × 160** |
| Size | **1.77 inch** |
| Interface | **SPI** |
| Rotation | **0** |
| CS | GPIO 5 |
| DC | GPIO 21 |
| RST | GPIO 22 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |

### 🎮 Four-Button Navigation

| Button | GPIO | Function |
|---|---:|---|
| ▲ UP | 32 | Move up |
| ▼ DOWN | 33 | Move down |
| OK / SELECT | 25 | Select |
| ↩ BACK | 34 | Return |

The display/menu layout is implemented by the firmware rather than being a separate mockup.

## 📋 Main Menu

The firmware menu is organized into modules such as:

```text
MRJ V2
├── Nethercap / Network Tools
├── Wi-Fi Tools
├── BLE Tools
├── Sub-GHz
├── NFC
├── RFID
├── iButton
├── IR Remote
├── BadUSB / HID
├── GPIO Control
├── Web Server
├── SD Card
└── Settings
```

> ⚠️ Some modules require additional hardware. Availability depends on the installed module and the corresponding firmware configuration.

## 🔧 Supported Hardware / Modules

### 🖥️ Display
- ST7735 TFT 1.77"
- 128×160 resolution
- SPI interface

### 💾 Storage
- MicroSD card
- SPI/HSPI storage interface
- Configuration and log storage

### 📡 Sub-GHz
- CC1101-compatible hardware
- SPI interface
- Frequency support depends on the hardware, firmware configuration, and local regulations

### 📳 NFC
- PN532
- I²C mode
- Compatible NFC/tag operations supported by the firmware

### 🪪 RFID
- MFRC522
- 125 kHz RFID hardware such as EM4100-compatible readers
- Module selection is required when resources are shared

### 🔑 iButton
- Dallas/iButton reader
- 1-Wire interface

### 🔴 Infrared
- IR receiver
- IR transmitter
- Remote-control related functions

### 📶 Wi-Fi / BLE
- ESP32 built-in Wi-Fi
- ESP32 Bluetooth/BLE
- Scanner and analysis-oriented modules

### 🔌 GPIO
- Digital input/output control
- Hardware testing
- Pin-state monitoring

## 🔀 Pin-Sharing Architecture

MRJ V2 uses a **shared-pin architecture** for selected optional modules.

```text
                 MRJ V2 PIN-SHARING
                         │
             ┌───────────┴───────────┐
             │                       │
          TEAM A                  TEAM B
             │                       │
       CH9326 + CC1101          NFC + RFID
             │                       │
             └──── Shared GPIO ──────┘
```

**Team A** and **Team B** are groups of modules that share GPIO resources. They are designed to operate **alternately, never simultaneously**.

This architecture allows multiple optional modules to be supported while reducing the number of dedicated GPIO pins required.

> ⚠️ Always verify the actual pin definitions in `hardware_pinout.h` before connecting hardware.

## 📁 Project Structure

```text
mrj_fw_v2/
├── platformio.ini
│
├── src/
│   ├── MRJ_FW_V2.ino
│   ├── config.h
│   ├── hardware_pinout.h
│   │
│   ├── display.h
│   ├── display.cpp
│   ├── menu.h
│   ├── menu.cpp
│   │
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
│   │
│   ├── web_server.h
│   ├── web_server.cpp
│   ├── ota_update.h
│   ├── ota_update.cpp
│   │
│   ├── wifi_scanner.h
│   ├── wifi_scanner.cpp
│   ├── wifi_deauth.h
│   ├── wifi_deauth.cpp
│   ├── nethercap_core.h
│   ├── nethercap_core.cpp
│   │
│   ├── ble_module.h
│   ├── ble_module.cpp
│   ├── ble_analyzer.h
│   ├── ble_analyzer.cpp
│   │
│   ├── subghz.h
│   ├── subghz.cpp
│   ├── subghz_analyzer.h
│   ├── subghz_analyzer.cpp
│   │
│   ├── nfc_module.h
│   ├── nfc_module.cpp
│   ├── nfc_analyzer.h
│   ├── nfc_analyzer.cpp
│   │
│   ├── rfid_module.h
│   ├── rfid_module.cpp
│   ├── rfid_125khz.h
│   ├── rfid_125khz.cpp
│   │
│   ├── ibutton.h
│   ├── ibutton.cpp
│   ├── ir_remote.h
│   ├── ir_remote.cpp
│   ├── ir_decoder.h
│   ├── ir_decoder.cpp
│   │
│   ├── badusb.h
│   ├── badusb.cpp
│   ├── ch9326.h
│   ├── ch9326.cpp
│   │
│   ├── gpio_control.h
│   └── gpio_control.cpp
│
├── data/
│   └── index.html
│
└── README.md
```

## 📦 Required Libraries

The exact dependencies are defined in **`platformio.ini`**.

Typical project components include:

| Component | Purpose |
|---|---|
| Adafruit GFX | Graphics primitives and text |
| Adafruit ST7735 | ST7735 TFT driver |
| SPI | Display/module communication |
| WiFi | ESP32 Wi-Fi functionality |
| WebServer | Local web interface |
| Preferences / EEPROM | Configuration storage |
| SD / FS | File and SD-card handling |
| Bluetooth / BLE | ESP32 Bluetooth functionality |
| Wire | I²C communication |
| PN532 library | NFC hardware support |
| MFRC522 library | RFID hardware support |

> **Tip:** Use PlatformIO to resolve libraries from `platformio.ini` whenever possible.

## 🛠️ Build With PlatformIO

### 1. Clone the repository

```bash
git clone https://github.com/j42844343-byte/mrj_v2-.git
cd mrj_v2-
```

### 2. Build

```bash
pio run
```

### 3. Upload

Connect the ESP32 by USB and run:

```bash
pio run -t upload
```

### 4. Serial Monitor

```bash
pio device monitor -b 115200
```

## 🧩 Configuration

Before connecting optional modules:

1. Check `src/config.h`
2. Check `src/hardware_pinout.h`
3. Check `src/reserved_pins.h`
4. Verify voltage levels
5. Verify SPI/I²C/UART connections
6. Make sure shared-pin modules are not enabled simultaneously

## 🧪 Development

The firmware is separated into modules so individual hardware functions can be developed and tested independently.

```text
MRJ_FW_V2.ino
      │
      ├── Config
      ├── Hardware Pinout
      ├── Display
      ├── Menu
      ├── Storage
      ├── Logging
      ├── Network
      ├── BLE
      ├── Sub-GHz
      ├── NFC / RFID
      ├── iButton
      ├── IR
      ├── HID
      └── GPIO
```

## ⚠️ Safety & Authorized Use

MRJ V2 is intended for:

- Educational electronics projects
- Firmware development
- Hardware testing
- Research in controlled environments
- Security testing on systems you own or are explicitly authorized to test

**Do not use the firmware to interfere with networks, devices, communications, credentials, or other systems without authorization.**

Follow applicable laws and radio regulations when using wireless hardware.

## 🤝 MRJ V2 Team

**MRJ V2 Team**

Built for:

> **Learning • Electronics • Firmware • Research • Innovation**

## 📜 Project Status

> 🚧 **Development project**

Features and hardware support may change as the firmware evolves.

## ⭐ Credits

- ESP32 ecosystem
- PlatformIO
- Arduino framework
- Adafruit graphics/display ecosystem
- Open-source hardware/software contributors
- **MRJ V2 Team**

<div align="center">

### 🟢 MRJ V2

**ESP32 Security & Electronics Toolkit**

**Educational • Research • Authorized Testing**

</div>
