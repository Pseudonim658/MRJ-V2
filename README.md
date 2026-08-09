# MRJ V2

<p align="center">
  <img src="mrj%20v2.png" alt="MRJ V2" width="420">
</p>

<p align="center">
  <b>MRJ V2 — ESP32 Multi-Function Hardware Toolkit</b><br>
  Modular firmware project for ESP32 with display, storage, wireless analysis, IR, RFID/NFC, iButton, GPIO and web features.
</p>

---

## ⚠️ Project Status

> **MRJ V2 is a hardware/firmware development project.**
>
> Some modules depend on the exact hardware connected to the ESP32 and may require additional libraries or configuration before use.

---

## ✨ Features

### 🖥️ Display & User Interface
- ST7735 TFT display support
- Configurable display settings
- Menu-based interface
- Button input handling
- Touch input support
- Buzzer/audio feedback

### 💾 Storage & System
- SD card support
- EEPROM configuration management
- Event/system logger
- Reserved GPIO pin management
- OTA firmware update support

### 📡 Wi-Fi
- Wi-Fi scanning
- Wi-Fi information display
- Web server interface
- Network-related analysis modules

### 🔵 Bluetooth / BLE
- Bluetooth module support
- BLE analysis module
- BLE device information/analysis

### 📻 Sub-GHz
- Sub-GHz transceiver interface
- Signal analysis framework
- Hardware-dependent frequency/protocol support

### 🪪 NFC & RFID
- NFC module interface
- NFC analysis framework
- RFID module interface
- 125 kHz RFID support

### 🔑 iButton
- iButton reader interface
- iButton data handling

### 📺 Infrared
- IR remote interface
- IR signal decoding
- IR signal handling

### 🔌 GPIO & USB/HID
- GPIO control
- CH9326 interface
- BadUSB/HID framework

> Use USB/HID functionality only on devices and systems where you have permission to test.

---

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
│   ├── reserved_pins.h
│   ├── reserved_pins.cpp
│   │
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
│   ├── wifi_deauth.h
│   ├── wifi_deauth.cpp
│   ├── nethercap_core.h
│   ├── nethercap_core.cpp
│   ├── wifi_scanner.h
│   ├── wifi_scanner.cpp
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
│   ├── gpio_control.cpp
│   ├── touch_driver.h
│   ├── touch_driver.cpp
│   │
│   ├── ota_update.h
│   ├── ota_update.cpp
│   ├── menu.h
│   └── menu.cpp
│
├── data/
│   └── index.html
│
└── README.md
```

---

## 🧩 Module Overview

| Module | Purpose |
|---|---|
| `display` | Display rendering and UI |
| `menu` | Main menu and navigation |
| `buzzer` | Audio feedback |
| `eeprom_manager` | Persistent configuration |
| `sd_card` | SD card storage |
| `logger` | System/event logging |
| `web_server` | Local web interface |
| `wifi_scanner` | Wi-Fi scanning |
| `ble_module` | Bluetooth/BLE hardware interface |
| `ble_analyzer` | BLE analysis |
| `subghz` | Sub-GHz hardware interface |
| `subghz_analyzer` | Sub-GHz analysis |
| `nfc_module` | NFC hardware interface |
| `nfc_analyzer` | NFC analysis |
| `rfid_module` | RFID hardware interface |
| `rfid_125khz` | 125 kHz RFID interface |
| `ibutton` | iButton interface |
| `ir_remote` | Infrared remote interface |
| `ir_decoder` | Infrared decoding |
| `gpio_control` | GPIO management |
| `touch_driver` | Touch input |
| `ch9326` | CH9326 interface |
| `badusb` | USB/HID framework |
| `ota_update` | OTA firmware update |
| `reserved_pins` | GPIO reservation management |

---

## 🛠️ Build Environment

MRJ V2 is designed around:

- **Platform:** ESP32
- **Framework:** Arduino
- **Build system:** PlatformIO
- **Language:** C/C++
- **Main firmware:** `src/MRJ_FW_V2.ino`

Build with:

```bash
pio run
```

Upload with:

```bash
pio run --target upload
```

Serial monitor:

```bash
pio device monitor
```

---

## ⚙️ Configuration

Hardware and firmware configuration should be checked before compiling.

Main configuration files:

```text
src/config.h
src/hardware_pinout.h
platformio.ini
```

Make sure the selected GPIO pins match the actual hardware connected to your ESP32.

---

## 🔧 Hardware

A typical MRJ V2 build can include:

- ESP32 development board
- TFT/OLED display
- Navigation buttons
- Buzzer
- SD card module
- NFC/RFID hardware
- iButton interface
- IR receiver/transmitter
- Sub-GHz transceiver
- Touch sensor
- Optional CH9326 USB/HID hardware

Exact hardware requirements depend on which modules are enabled.

---

## 📌 Safety & Responsible Use

MRJ V2 is intended for:

- electronics learning
- firmware development
- hardware testing
- authorized security research
- laboratory environments
- analysis of devices you own or have permission to test

Do not use wireless, RFID/NFC, IR, USB/HID, or network functionality to interfere with systems, access devices without authorization, or disrupt other users.

---

## 🚀 Development

The project is organized into separate `.h` and `.cpp` modules so individual hardware features can be developed and tested independently.

Recommended development flow:

```text
Hardware
   ↓
Pin configuration
   ↓
Module driver
   ↓
Analyzer / controller
   ↓
Menu
   ↓
Display / Web UI
   ↓
MRJ V2 firmware
```

---

## 👥 MRJ V2 Team

**By MRJ V2 Team**

Firmware, hardware integration, UI, testing, and development are organized as a modular open project.

---

## 📜 License

Choose and add an appropriate license before distributing the project publicly.

If this repository contains third-party libraries, follow the license terms of each dependency.

---

## ⭐ MRJ V2

**Build • Learn • Test • Create**

<p align="center">
  <b>MRJ V2 Team</b>
</p>
