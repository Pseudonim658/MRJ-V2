<div align="center">⚡ MRJ FW V2

ESP32 Multi-Display Firmware Platform

Modular · Fast · Configurable · Maker Friendly

<br>""ESP32" (https://img.shields.io/badge/ESP32-DevKit%20V1-0A7BFF?style=for-the-badge&logo=espressif)" (https://www.espressif.com/)
""Firmware" (https://img.shields.io/badge/Firmware-v2.1.0-7C3AED?style=for-the-badge)"
""Displays" (https://img.shields.io/badge/Displays-14%20Variants-00A86B?style=for-the-badge)"
""Build" (https://img.shields.io/badge/Build-Passing-00C853?style=for-the-badge)"
""License" (https://img.shields.io/badge/License-MIT-22C55E?style=for-the-badge)"

<br><br>

""🌐 OPEN WEB" (https://img.shields.io/badge/🌐%20OPEN%20WEB-Visit%20Website-e5a34a?style=for-the-badge&logo=googlechrome)" (ISI_LINK_WEB_KAMU)

<br><br>

<img src="mrj.png" alt="MRJ FW V2" width="900"><br>⚡ Universal ESP32 Display Firmware

OLED • TFT • SPI • I²C • Web • Wireless • Modular

</div>---

🧭 Navigation

"🚀 About" (#-about-mrj-fw-v2) ·
"✨ Features" (#-features) ·
"🖥️ Displays" (#️-display-support) ·
"🔌 Pinout" (#-pinout) ·
"🏗️ Architecture" (#️-architecture) ·
"📚 Libraries" (#-libraries) ·
"⚙️ Build" (#️-build) ·
"⚡ Flash" (#-flash) ·
"📁 Structure" (#-project-structure) ·
"📊 Status" (#-project-status)

---

🚀 About MRJ FW V2

MRJ FW V2 adalah platform firmware modular untuk ESP32 DevKit V1 yang mendukung berbagai jenis OLED dan TFT display dalam satu ekosistem.

Project ini dibuat untuk maker, embedded developer, teknisi, dan eksperimen elektronik dengan fokus pada struktur firmware yang modular dan mudah dikembangkan.

🧠 Core System

                         ⚡ MRJ FW V2
                              │
          ┌───────────────────┼───────────────────┐
          │                   │                   │
       🖥️ DISPLAY           🌐 WEB              📡 WIRELESS
          │                   │                   │
      OLED / TFT         Async Server       Wi-Fi / BLE
          │                   │                   │
          └───────────────────┼───────────────────┘
                              │
                     ┌────────┴────────┐
                     │                 │
                  💾 STORAGE        🔌 HARDWARE
                     │                 │
                 SD / EEPROM      GPIO / Modules

---

✨ Features

🖥️ Display System

- 14 display variants
- OLED SSD1306
- OLED SH1106
- TFT ST7735
- TFT ST7789
- TFT ILI9341
- TFT ILI9488
- TFT_eSPI support
- Resolution hingga 320×480
- Modular display architecture

🌐 Web Interface

- Local Web UI
- Async Web Server
- Device control
- Configuration interface
- Status monitoring

📡 Wireless

- Wi-Fi scanner
- BLE scanner
- Wireless analyzer modules
- Modular wireless architecture

💾 Storage

- SD Card support
- EEPROM configuration
- OTA architecture
- Logging system

🔌 Hardware

- GPIO control
- Buzzer
- Touch input
- IR remote
- iButton
- NFC
- RFID
- Sub-GHz
- Battery monitoring

---

🖥️ Display Support

🟢 OLED Family — I²C

Variant| Driver| Resolution| Interface
"OLED_096_SSD1306_128x64"| SSD1306| 128×64| I²C
"OLED_13_SSD1306_128x64"| SSD1306| 128×64| I²C
"OLED_15_SH1106_128x64"| SH1106| 128×64| I²C
"OLED_20_SSD1306_128x64"| SSD1306| 128×64| I²C
"OLED_242_SH1106_128x64"| SH1106| 128×64| I²C

🔵 TFT Family — SPI

Variant| Driver| Resolution| Interface
"TFT_13_ST7789_240x240"| ST7789| 240×240| SPI
"TFT_154_ST7789_240x240"| ST7789| 240×240| SPI
"TFT_177_ST7735_128x160"| ST7735/S| 128×160| SPI
"TFT_18_ST7735_128x160"| ST7735| 128×160| SPI
"TFT_20_ST7789_240x320"| ST7789| 240×320| SPI
"TFT_24_ILI9341_240x320"| ILI9341| 240×320| SPI
"TFT_24_ST7789_240x320"| ST7789| 240×320| SPI
"TFT_28_ILI9341_240x320"| ILI9341| 240×320| SPI
"TFT_35_ILI9488_TFT_eSPI"| ILI9488| 320×480| SPI

«14 display variants · One firmware ecosystem»

---

🔌 Pinout

I²C Bus

ESP32 Pin| Peripheral| Function
GPIO 21| SDA| I²C Data
GPIO 22| SCL| I²C Clock
3.3V| VCC| Power
GND| GND| Ground

VSPI Bus

ESP32 Pin| Peripheral| Function
GPIO 23| MOSI| SPI Data
GPIO 19| MISO| SPI Input
GPIO 18| SCK| SPI Clock
GPIO 5| TFT_CS| Display Select
GPIO 2| TFT_DC| Data / Command
GPIO 4| SD_CS| SD Select
GPIO 21| TP_CS| Touch Select

🔐 Team A/B SPI Management

Peripheral yang menggunakan bus SPI bersama dikelola menggunakan sistem Team A/B.

                       ESP32
                         │
                      VSPI BUS
                         │
              ┌──────────┴──────────┐
              │                     │
           TEAM A                 TEAM B
              │                     │
           ACTIVE                STANDBY
              │                     │
              └──────────┬──────────┘
                         │
                    SPI Manager

Sistem ini membantu mengatur akses peripheral agar tidak terjadi konflik ketika bus SPI digunakan bersama.

---

🏗️ Architecture

MRJ FW V2 menggunakan struktur modular sehingga komponen firmware dapat dikembangkan secara terpisah.

                         MRJ FW V2
                            │
       ┌────────────────────┼────────────────────┐
       │                    │                    │
    DISPLAY               CORE                  WEB
       │                    │                    │
 ┌─────┴─────┐       ┌──────┴──────┐       ┌─────┴─────┐
 │ OLED      │       │ Config      │       │ Async     │
 │ TFT       │       │ EEPROM      │       │ Web UI    │
 │ Drivers   │       │ Logger      │       │ API       │
 └───────────┘       │ Storage     │       └───────────┘
                     └──────┬──────┘
                            │
              ┌─────────────┼─────────────┐
              │             │             │
            Wi-Fi          BLE        Hardware
              │             │             │
           Scanner       Scanner      Modules

---

📚 Libraries

Library utama yang digunakan:

- "Adafruit GFX Library"
- "Adafruit SSD1306"
- "Adafruit SH110X"
- "Adafruit ST7735 and ST7789 Library"
- "Adafruit ILI9341"
- "TFT_eSPI"
- "ESPAsyncWebServer"
- "AsyncTCP"
- "ArduinoJson"
- "U8g2"

---

⚙️ Build

PlatformIO

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200
upload_speed = 921600

board_build.f_cpu = 240000000L

Build

pio run

Upload

pio run -t upload

Serial Monitor

pio device monitor

---

⚡ Flash

Jika sudah memiliki file firmware ".bin":

esptool.py \
  --chip esp32 \
  --port /dev/ttyUSB0 \
  --baud 921600 \
  write_flash 0x10000 firmware.bin

Jika koneksi tidak stabil:

esptool.py \
  --chip esp32 \
  --port /dev/ttyUSB0 \
  --baud 460800 \
  write_flash 0x10000 firmware.bin

«Note: Gunakan alamat flash yang sesuai dengan hasil build firmware. Untuk project dengan bootloader dan partition table khusus, ikuti alamat yang diberikan oleh build system.»

---

📁 Project Structure

MRJ-V2/
│
├── .github/
│   └── workflows/
│       └── build-firmware.yml
│
├── oled_variants/
│   ├── OLED_096_SSD1306_128x64/
│   ├── OLED_13_SSD1306_128x64/
│   ├── OLED_15_SH1106_128x64/
│   ├── OLED_20_SSD1306_128x64/
│   └── OLED_242_SH1106_128x64/
│
├── tft_source_zips/
│   ├── TFT_13_ST7789_240x240_source.zip
│   ├── TFT_154_ST7789_240x240_source.zip
│   ├── TFT_177_ST7735_128x160_source.zip
│   ├── TFT_18_ST7735_128x160_source.zip
│   ├── TFT_20_ST7789_240x320_source.zip
│   ├── TFT_24_ILI9341_240x320_source.zip
│   ├── TFT_24_ST7789_240x320_source.zip
│   ├── TFT_28_ILI9341_240x320_source.zip
│   └── TFT_35_ILI9488_TFT_eSPI_source.zip
│
├── src/
│   ├── MRJ_FW_V2.ino
│   ├── config.h
│   ├── hardware_pinout.h
│   ├── display.cpp
│   ├── display.h
│   ├── web_server.cpp
│   ├── web_server.h
│   ├── wifi_scanner.cpp
│   ├── ble_module.cpp
│   ├── sd_card.cpp
│   ├── eeprom_manager.cpp
│   ├── logger.cpp
│   └── ...
│
├── mrj.png
├── platformio.ini
├── README.md
└── LICENSE

---

📊 Project Status

Component| Status
🖥️ OLED Family| ✅
📺 TFT Family| ✅
ST7735| ✅
ST7789| ✅
ILI9341| ✅
ILI9488| ✅
🌐 Web Server| ✅
📡 Wi-Fi Scanner| ✅
🔵 BLE Module| ✅
💾 SD Card| ✅
🧠 EEPROM| ✅
🔄 OTA| ✅
🔌 GPIO| ✅
⚡ SPI Manager| ✅
🤖 Modular Architecture| ✅

---

🛠️ Troubleshooting

OLED tidak menyala

Periksa:

SDA → GPIO 21
SCL → GPIO 22
VCC → 3.3V
GND → GND

Alamat I²C umum:

0x3C
0x3D

TFT blank / white screen

Periksa:

MOSI
SCK
CS
DC
RST
VCC
GND

Pastikan driver dan konfigurasi pin sesuai dengan display yang digunakan.

Upload gagal

Coba:

pio run -t upload

atau gunakan baud lebih rendah:

460800

---

🤝 Contributing

Kontribusi untuk driver display, modul hardware, dokumentasi, optimasi firmware, dan improvement lainnya dipersilakan.

Sebelum Pull Request:

- Pastikan project berhasil di-build.
- Dokumentasikan perubahan.
- Periksa pinout.
- Periksa dependency.
- Pastikan varian display lain tidak rusak.

---

📄 License

Released under the MIT License.

---

<div align="center">⚡ MRJ FW V2

Multi-Display Firmware for ESP32

Build · Flash · Configure · Create

<br>🌐 WEB

""OPEN WEB" (https://img.shields.io/badge/🌐%20OPEN%20WEB-Visit%20Website-e5a34a?style=for-the-badge&logo=googlechrome)" (ISI_LINK_WEB_KAMU)

<br>"MRJ FW V2 · ESP32 · 14 Display Variants"

</div>
