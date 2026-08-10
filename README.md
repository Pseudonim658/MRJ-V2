# MRJ V2 — Modular Research Jack

> **Universal ESP32 Display Firmware & Modular Hardware Toolkit**

![MRJ V2](mrj%20v2.png)

MRJ V2 is an ESP32-based modular hardware platform designed for electronics research, experimentation, diagnostics, and development.

The firmware supports multiple **TFT and OLED displays**, SD storage, IR, iButton, NFC/RFID interfaces, Sub-GHz hardware interfaces, GPIO control, and a modular firmware architecture.

---

## ✨ Features

| Feature | Support |
|---|:---:|
| ESP32 DevKit V1 | ✅ |
| Universal Display Support | ✅ |
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
| Battery Monitoring | ⚠️ |
| Web Interface | 🔧 |
| OTA Update | 🔧 |
| Modular Architecture | ✅ |

---

# 🖥️ Display Support

MRJ V2 supports **13 display variants**.

## TFT Displays

| Size | Driver | Resolution | Interface |
|---|---|---:|---|
| 1.8" | ST7735 | 128×160 | SPI |
| 1.3" | ST7789 | 240×240 | SPI |
| 1.54" | ST7789 | 240×240 | SPI |
| 2.0" | ST7789 | 240×320 | SPI |
| 2.4" | ST7789 | 240×320 | SPI |
| 2.4" | ILI9341 | 240×320 | SPI |
| 2.8" | ILI9341 | 240×320 | SPI |
| 3.5" | ILI9488 | 320×480 | SPI |

## OLED Displays

| Size | Driver | Resolution | Interface |
|---|---|---:|---|
| 0.96" | SSD1306 | 128×64 | I2C |
| 1.3" | SSD1306 | 128×64 | I2C |
| 1.5" | SH1106 | 128×64 | I2C |
| 2.0" | SSD1306 | 128×64 | I2C |
| 2.42" | SH1106 | 128×64 | I2C |

---

# 🔌 ESP32 Pinout

## Fixed Pins

| Function | GPIO |
|---|---:|
| SD SCK | `14` |
| SD MISO | `26` |
| SD MOSI | `27` |
| SD CS | `4` |
| I2C SDA | `16` |
| I2C SCL | `17` |
| IR Receiver | `36` |
| IR Transmitter | `12` |
| iButton | `2` |
| Buzzer | `13` |
| Button UP | `32` |
| Button DOWN | `33` |
| Button SELECT | `25` |
| Button BACK | `34` |

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
```

### SPI Pins

| TFT Pin | ESP32 |
|---|---:|
| SCK | GPIO 18 |
| MISO | GPIO 19 |
| MOSI | GPIO 23 |
| CS | GPIO 5 |
| DC | GPIO 21 |
| RST | GPIO 22 |

---

# 🟦 OLED Pinout

```text
OLED
│
├── VCC → 3.3V
├── GND → GND
├── SDA → GPIO 16
└── SCL → GPIO 17
```

### I2C Addresses

```text
OLED  → 0x3C
PN532 → 0x24
```

The OLED and PN532 can share the same I2C bus when their addresses are different.

---

# 📡 Optional Hardware

## Sub-GHz — CC1101

```text
CS → GPIO 5
```

Optional GDO pins can be assigned depending on the CC1101 module and firmware configuration.

## RFID — MFRC522

```text
CS  → GPIO 15
RST → GPIO 21
```

## NFC — PN532

```text
SDA → GPIO 16
SCL → GPIO 17
I2C Address → 0x24
```

## IR

```text
IR Receiver → GPIO 36
IR LED      → GPIO 12
```

## iButton

```text
DS1990 / iButton → GPIO 2
```

## Buzzer

```text
Buzzer → GPIO 13
```

---

# 🎮 Controls

MRJ V2 uses four physical buttons:

```text
        ┌─────────┐
        │   UP    │
        ├─────────┤
        │  DOWN   │
        ├─────────┤
        │ SELECT  │
        ├─────────┤
        │  BACK   │
        └─────────┘
```

| Button | GPIO |
|---|---:|
| UP | `32` |
| DOWN | `33` |
| SELECT | `25` |
| BACK | `34` |

---

# 🔀 TFT Module Sharing

TFT builds use SPI for the display.

Because the SPI bus is shared, optional modules should be configured so that conflicting devices are not accessed simultaneously.

```text
             VSPI
              │
       ┌──────┼──────┐
       │      │      │
      TFT   CC1101  MFRC522
       │
       └── Shared SPI
```

The firmware should manage chip-select lines and module activation carefully.

---

# 🟦 OLED Module Architecture

OLED displays use I2C, leaving the VSPI interface available for additional hardware.

```text
             ESP32
               │
       ┌───────┼────────┐
       │       │        │
      OLED    PN532   SPI Modules
       │       │        │
       └── I2C ┘        └── VSPI
```

This allows multiple independent interfaces to coexist, provided their electrical connections and chip-select lines are configured correctly.

---

# 📚 Libraries

## Core

```ini
bblanchon/ArduinoJson
me-no-dev/AsyncTCP
me-no-dev/ESP Async WebServer
DNSServer
```

## TFT

```ini
adafruit/Adafruit ST7735 and ST7789 Library
adafruit/Adafruit ILI9341
adafruit/Adafruit GFX Library
```

## OLED

```ini
adafruit/Adafruit SSD1306
adafruit/Adafruit GFX Library
olikraus/U8g2
```

---

# ⚙️ Display Build Flags

## TFT

```text
MRJ_DISPLAY_ST7735_18
MRJ_DISPLAY_ST7789_13
MRJ_DISPLAY_ST7789_154
MRJ_DISPLAY_ST7789_20
MRJ_DISPLAY_ST7789_24
MRJ_DISPLAY_ILI9341_24
MRJ_DISPLAY_ILI9341_28
MRJ_DISPLAY_ILI9488_35
```

## OLED

```text
MRJ_DISPLAY_SSD1306_096
MRJ_DISPLAY_SSD1306_13
MRJ_DISPLAY_SH1106_15
MRJ_DISPLAY_SSD1306_20
MRJ_DISPLAY_SH1106_242
```

---

# 🛠️ PlatformIO

Example for **OLED 0.96" SSD1306**:

```ini
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
```

---

# 📁 Project Structure

```text
mrj_fw_v2/
│
├── platformio.ini
│
├── src/
│   ├── MRJ_FW_V2.ino
│   │
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
│   ├── wifi_deauth.h
│   ├── wifi_deauth.cpp
│   │
│   ├── nethercap_core.h
│   ├── nethercap_core.cpp
│   │
│   ├── wifi_scanner.h
│   ├── wifi_scanner.cpp
│   │
│   ├── ble_module.h
│   ├── ble_module.cpp
│   │
│   ├── ble_analyzer.h
│   ├── ble_analyzer.cpp
│   │
│   ├── subghz.h
│   ├── subghz.cpp
│   │
│   ├── subghz_analyzer.h
│   ├── subghz_analyzer.cpp
│   │
│   ├── nfc_module.h
│   ├── nfc_module.cpp
│   │
│   ├── nfc_analyzer.h
│   ├── nfc_analyzer.cpp
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
│   ├── touch_driver.h
│   ├── touch_driver.cpp
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

# 🧩 Firmware Architecture

```text
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
```

---

# ⚡ Power

MRJ V2 is designed around a **3.3V logic environment**.

Typical current depends heavily on the selected display and connected modules.

> ⚠️ Always verify the voltage requirements of each module before connecting it to the ESP32.

Do not assume every breakout board is 3.3V-safe just because its controller is 3.3V.

---

# ⚠️ Hardware Notes

- Verify your exact ESP32 DevKit pinout before wiring.
- GPIO34–39 are input-only on classic ESP32.
- GPIO34 does not provide an internal pull-up, so an external pull-up may be required.
- GPIO36/39 are input-only.
- Avoid powering high-current peripherals directly from an ESP32 GPIO.
- Use proper level shifting where required.
- Check SPI chip-select conflicts before enabling multiple modules.
- Verify I2C addresses before connecting multiple I2C devices.

---

# 🔐 Responsible Use

MRJ V2 is intended for:

- Electronics learning
- Hardware experimentation
- RF research
- Device diagnostics
- Development
- Testing equipment you own or have explicit permission to test

Use wireless, RFID/NFC, IR, HID, and other interfaces only in accordance with applicable laws and with proper authorization.

---

# 🚀 Build

```bash
pio run
```

Upload:

```bash
pio run -t upload
```

Serial monitor:

```bash
pio device monitor
```

---

# 📦 Releases

Firmware binaries can be distributed through GitHub Releases.

Example:

```text
MRJ V2
├── Firmware
├── Bootloader
└── Partition Table
```

---

# 👥 MRJ V2 Team

**MRJ V2 Team**

> **MRJ — Modular Research Jack**

### Build • Learn • Experiment

---

## ⭐ Project

If MRJ V2 is useful to you, consider giving the project a ⭐ on GitHub.

**MRJ V2 — One ESP32. Multiple Displays. Modular Hardware.**
