<div align="center">

<img src="mrj.png" alt="MRJ FW V2 Logo" width="160"/>

# ⚡ MRJ FW V2

**Multi-Display Firmware Platform for ESP32**

[![Platform](https://img.shields.io/badge/platform-ESP32-orange)](https://www.espressif.com/en/products/socs/esp32)
[![Language](https://img.shields.io/badge/language-C%2B%2B-blue)](https://isocpp.org/)
[![Arduino CLI](https://img.shields.io/badge/Arduino-CLI-00979C)](https://github.com/arduino/arduino-cli)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-2.1.0-blue.svg)](https://github.com/Pseudonim658/MRJ-V2/releases)
[![GitHub Stars](https://img.shields.io/github/stars/Pseudonim658/MRJ-V2?style=social)](https://github.com/Pseudonim658/MRJ-V2/stargazers)
[![GitHub Forks](https://img.shields.io/github/forks/Pseudonim658/MRJ-V2?style=social)](https://github.com/Pseudonim658/MRJ-V2/network/members)
[![GitHub Watchers](https://img.shields.io/github/watchers/Pseudonim658/MRJ-V2?style=social)](https://github.com/Pseudonim658/MRJ-V2/watchers)

*Modular · Fast · Configurable · Maker Friendly*

**🌐 [mrj-fw.my.id](https://mrj-fw.my.id)** — Project information, documentation, firmware information, and demos.

</div>

## 📌 About

MRJ FW V2 is a modular firmware platform designed for the **ESP32 DevKit V1**.

The project provides a unified firmware ecosystem for multiple OLED and TFT displays, with individual display variants containing their own configuration, display drivers, and build files.

MRJ FW V2 is designed for:

- Makers and hobbyists
- Embedded developers
- Electronics experimentation
- ESP32 projects
- IoT prototyping
- Custom hardware development

## ✨ Features

| Module | Support |
|---|---|
| 🖥️ Display | OLED and TFT display variants |
| 🌐 Web Interface | Configuration, monitoring and OTA firmware update |
| 📡 Wi-Fi | Wi-Fi scanning and wireless utilities |
| 🔵 Bluetooth | BLE-related functionality |
| 💾 Storage | SD Card, EEPROM and logging |
| 🔌 GPIO | GPIO control and hardware management |
| 🔊 Buzzer | Buzzer control |
| 👆 Touch | Touch input |
| 📺 IR | IR remote functionality |
| 🔑 iButton | iButton interface |
| 📡 NFC | NFC module support |
| 🪪 RFID | RFID module support |
| 📻 Sub-GHz | Sub-GHz module support |
| 🔋 Battery | Battery voltage monitoring |
| 🔄 OTA | Wireless firmware update |

## 📁 Project Structure

```
MRJ-V2/
├── OLED_096_SSD1306_128x64/
├── OLED_13_SSD1306_128x64/
├── OLED_15_SH1106_128x64/
├── OLED_20_SSD1306_128x64/
├── OLED_242_SH1106_128x64/
├── TFT_13_ST7789_240x240/
├── TFT_154_ST7789_240x240/
├── TFT_177_ST7735_128x160/
├── TFT_18_ST7735_128x160/
├── TFT_20_ST7789_240x320/
├── TFT_24_ILI9341_240x320/
├── TFT_24_ST7789_240x320/
├── TFT_28_ILI9341_240x320/
├── TFT_35_ILI9488_TFT_eSPI/
├── .github/
│   └── workflows/
├── mrj.png
└── README.md
```

Individual display projects may contain files such as:

- `config.h`
- `display.h`
- `display.cpp`
- `compile.sh`
- `logger.h`
- `reserved_pins.cpp`

## 🖥️ Supported Displays

### OLED — I²C

| Display | Driver | Resolution | Directory |
|---|---|---|---|
| OLED 0.96" | SSD1306 | 128×64 | `OLED_096_SSD1306_128x64/` |
| OLED 1.3" | SSD1306 | 128×64 | `OLED_13_SSD1306_128x64/` |
| OLED 1.5" | SH1106 | 128×64 | `OLED_15_SH1106_128x64/` |
| OLED 2.0" | SSD1306 | 128×64 | `OLED_20_SSD1306_128x64/` |
| OLED 2.42" | SH1106 | 128×64 | `OLED_242_SH1106_128x64/` |

### TFT — SPI

| Display | Driver | Resolution | Directory |
|---|---|---|---|
| TFT 1.3" | ST7789 | 240×240 | `TFT_13_ST7789_240x240/` |
| TFT 1.54" | ST7789 | 240×240 | `TFT_154_ST7789_240x240/` |
| TFT 1.77" | ST7735 | 128×160 | `TFT_177_ST7735_128x160/` |
| TFT 1.8" | ST7735 | 128×160 | `TFT_18_ST7735_128x160/` |
| TFT 2.0" | ST7789 | 240×320 | `TFT_20_ST7789_240x320/` |
| TFT 2.4" | ILI9341 | 240×320 | `TFT_24_ILI9341_240x320/` |
| TFT 2.4" | ST7789 | 240×320 | `TFT_24_ST7789_240x320/` |
| TFT 2.8" | ILI9341 | 240×320 | `TFT_28_ILI9341_240x320/` |
| TFT 3.5" | ILI9488 / TFT_eSPI | 320×480 | `TFT_35_ILI9488_TFT_eSPI/` |

## 🔌 Pinout

### OLED — I²C

| ESP32 GPIO | Function |
|---|---|
| GPIO 21 | SDA |
| GPIO 22 | SCL |
| 3.3V | VCC |
| GND | GND |

Default I²C addresses: `0x3C`, `0x3D`

### TFT — SPI

| ESP32 GPIO | Function |
|---|---|
| GPIO 23 | MOSI |
| GPIO 19 | MISO |
| GPIO 18 | SCK |
| GPIO 5 | CS |
| GPIO 2 | DC |
| GPIO 4 | RST / peripheral CS |

> Pin assignments can vary between display variants. Always check the `config.h` and hardware documentation inside the selected variant directory.

## 🏗️ Code Architecture

Each display variant is designed to keep its configuration and display-specific implementation separate.

```
Display Variant
├── config.h
├── display.h
├── display.cpp
├── compile.sh
└── additional modules
```

**`config.h`** — Contains display-specific settings such as:
- Display driver
- Resolution
- GPIO configuration
- SPI/I²C configuration
- Display options

**`display.cpp`** — Contains:
- Display initialization
- Rendering functions
- Screen updates
- Display-specific implementation

**`display.h`** — Contains display interfaces and declarations used by the firmware.

**`compile.sh`** — Optional helper script for Arduino CLI compilation.

## ⚙️ Build With Arduino CLI

Install the ESP32 Arduino platform first:

```bash
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

Enter the desired display directory:

```bash
cd TFT_18_ST7735_128x160
```

Compile:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 .
```

Upload:

```bash
arduino-cli upload --fqbn esp32:esp32:esp32 --port /dev/ttyUSB0 .
```

If the project contains `compile.sh`:

```bash
chmod +x compile.sh
./compile.sh
```

## 🔧 PlatformIO

If the selected variant contains a PlatformIO project:

```bash
pio run
```

Upload:

```bash
pio run -t upload
```

Monitor serial output:

```bash
pio device monitor -b 115200
```

## ⚡ Flashing Firmware (.bin)

If a compiled firmware binary is available:

```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600 write_flash 0x10000 firmware.bin
```

For unstable connections:

```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 write_flash 0x10000 firmware.bin
```

> The correct flash address depends on how the firmware was built. For a complete Arduino/PlatformIO image, use the generated flashing command or complete firmware image when applicable.

## 🌐 Web Interface

When the firmware variant includes the web interface, the ESP32 can provide a local configuration interface.

Default access point:

- **SSID:** `MRJ_AP`
- **Address:** `http://192.168.4.1`

Available functions may include:

| Feature | Description |
|---|---|
| 🔄 OTA Update | Upload firmware wirelessly |
| 🖥️ Display Information | Display configuration and status |
| 📊 System Monitor | Runtime and system information |
| ⚙️ Settings | Device configuration |
| 🔌 GPIO | GPIO management |
| 📡 Wi-Fi | Wireless configuration and tools |

> Web-interface features depend on the firmware build and enabled modules.

## 🛠️ Troubleshooting

**OLED does not work**

Check:
- OLED VCC → ESP32 3.3V
- OLED GND → ESP32 GND
- OLED SDA → GPIO 21
- OLED SCL → GPIO 22

Also check the I²C address: `0x3C`, `0x3D`

**TFT shows a white or blank screen**

Check:
- MOSI
- MISO
- SCK
- CS
- DC
- RST
- Display driver
- Display resolution
- Power supply

Make sure the selected firmware matches the physical display.

**Upload fails**

Try:
1. Check the USB cable.
2. Select the correct serial port.
3. Press the BOOT button during upload if required.
4. Reduce the upload speed.
5. Reset the ESP32 and try again.

**SPI conflict**

Some peripherals share the SPI bus. Check the selected variant's pin configuration and make sure that:
- CS pins are unique.
- Shared SPI pins are configured correctly.
- Two peripherals are not accidentally using the same CS pin.

## 🤝 Contributing

Contributions are welcome. You can contribute:

- New display drivers
- New display variants
- Hardware modules
- Bug fixes
- Performance improvements
- Documentation
- Build improvements

Before submitting a Pull Request:

1. Make sure the affected firmware builds successfully.
2. Test the hardware when possible.
3. Check that existing display variants are not broken.
4. Update documentation when required.

## 📄 License

MRJ FW V2 is released under the **MIT License**.

You are free to:

- Use the software
- Modify the software
- Distribute copies
- Use it for personal projects
- Use it in commercial projects

See the repository license file for the complete license text.

## 🙏 Acknowledgements

MRJ FW V2 uses and/or builds upon technologies from:

- Arduino
- Arduino CLI
- PlatformIO
- Adafruit display libraries
- U8g2
- TFT_eSPI
- ESP32 Arduino Core

Thanks to the open-source community and everyone contributing to ESP32 development.

<div align="center">

**⚡ MRJ FW V2** — One firmware platform for multiple ESP32 displays.

© 2026 MRJ Team

</div>
