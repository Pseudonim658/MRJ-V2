# MRJ V2

<p align="center">
  <img src="mrj%20v2.png" alt="MRJ V2" width="700">
</p>

<h3 align="center">MRJ V2 — ESP32 Security & Electronics Toolkit</h3>

<p align="center">
  Modular ESP32 firmware for electronics development, hardware testing, diagnostics, and authorized security research.
</p>

## About

MRJ V2 is a modular firmware project for the ESP32 DevKit V1.

The project combines display, storage, wireless communication, NFC, RFID, infrared, iButton, GPIO, web interface, OTA update, logging, and other hardware modules into one firmware architecture.

> Educational and authorized security testing only.
>
> Use MRJ V2 only with devices, networks, cards, tags, radios, and systems that you own or have explicit permission to test.

## Features

### Display

- TFT ST7735 1.77" 128x160
- SPI display support
- Graphical user interface
- Menu system
- Status screens
- Hardware information
- OLED alternative display support
- Adafruit GFX graphics support

### Storage

- SD card support
- Configuration storage
- File storage
- Log storage
- Firmware data storage
- SD card management

### Configuration

- EEPROM configuration manager
- Persistent settings
- Hardware configuration
- Reserved GPIO management
- Central configuration system

### Wi-Fi

- ESP32 Wi-Fi support
- Wi-Fi scanner
- Access point information
- Network information
- Wireless diagnostics
- Web server integration
- Controlled wireless testing components

### BLE

- Bluetooth support
- BLE module management
- BLE device analysis
- BLE information
- BLE diagnostics

### Sub-GHz

- CC1101 support
- VSPI interface
- Radio module management
- GDO support
- Sub-GHz diagnostics
- Signal analysis framework

Use only legal frequencies and authorized radio equipment.

### NFC

- PN532 support
- I2C communication
- NFC/tag reading
- NFC module management
- Optional IRQ support
- NFC analysis

### RFID

- MFRC522 support
- SPI communication
- RFID module management
- RFID card/tag interaction
- 125 kHz RFID support
- EM4100-related RFID support
- UART RFID interface

### Infrared

- IR receiver
- IR transmitter
- IR decoder
- IR remote functions
- GPIO-based IR interface
- Signal analysis

### iButton

- Dallas/iButton reader
- iButton interface
- Device identification
- Reader management

### GPIO

- Digital input
- Digital output
- GPIO testing
- Pin monitoring
- GPIO control
- Reserved-pin protection

### Touch

- Touch driver
- Touch input
- Menu interaction
- Hardware input handling

### Buzzer

- Buzzer driver
- System notifications
- Menu feedback
- Status sounds
- Error alerts

### Web Server

- ESP32 web server
- Browser interface
- Device information
- Configuration interface
- Firmware management
- Web-based controls

### OTA

- Over-The-Air update framework
- Firmware update management
- Update status
- Remote firmware management

### Logging

- System logs
- Debug messages
- Error messages
- Module status
- SD-card logging

### Menu

- Main menu
- Module menus
- Navigation
- Configuration screens
- Hardware status
- Feature selection

### USB / HID

- USB/HID testing framework
- CH9326 interface
- UART communication
- HID-related hardware support

## Project Structure

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
├── mrj v2.png
│
└── README.md
Module Overview
Module
Function
MRJ_FW_V2.ino
Main firmware
config.h
Global configuration
hardware_pinout.h
Hardware pin definitions
display
TFT/OLED display system
reserved_pins
GPIO reservation
eeprom_manager
Persistent configuration
buzzer
Buzzer control
sd_card
SD card management
logger
System logging
web_server
Web interface
wifi_deauth
Controlled Wi-Fi testing component
nethercap_core
Network analysis core
wifi_scanner
Wi-Fi scanning
ble_module
Bluetooth/BLE management
ble_analyzer
BLE analysis
subghz
CC1101/Sub-GHz interface
subghz_analyzer
Sub-GHz analysis
nfc_module
PN532 NFC interface
nfc_analyzer
NFC analysis
rfid_module
MFRC522 RFID interface
rfid_125khz
125 kHz RFID interface
ibutton
iButton interface
ir_remote
IR transmit/receive
ir_decoder
IR decoding
badusb
USB/HID testing framework
ch9326
CH9326 interface
gpio_control
GPIO control
touch_driver
Touch input
ota_update
OTA updates
menu
User interface
Architecture
                         MRJ V2
                           |
             +-------------+-------------+
             |             |             |
           Display       Menu        Configuration
             |             |             |
             +-------------+-------------+
                           |
                    Hardware Manager
                           |
       +---------+---------+---------+---------+
       |         |         |         |         |
      Wi-Fi     BLE      NFC/RFID   IR     Sub-GHz
       |         |         |         |         |
       +---------+---------+---------+---------+
                           |
                    Storage / Logging
                           |
                    SD Card / EEPROM
                           |
                    Web Server / OTA
Hardware
Controller
ESP32 DevKit V1
ESP32 30-pin board
Arduino framework
PlatformIO
Supported Hardware
Hardware
Interface
ST7735 TFT
SPI
OLED
I2C
SD Card
SPI
PN532
I2C
MFRC522
SPI
125 kHz RFID
UART
CC1101
SPI
IR Receiver
GPIO
IR Transmitter
GPIO
iButton
GPIO
Buzzer
GPIO
Touch Sensor
GPIO
CH9326
UART
Wi-Fi
ESP32 internal
BLE
ESP32 internal
Build Environment
MRJ V2 is designed for PlatformIO.
Example:
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_speed = 921600
Build
Clone the repository:
git clone https://github.com/j42844343-byte/mrj_v2-.git
cd mrj_v2-
Build:
pio run
Upload:
pio run --target upload
Serial monitor:
pio device monitor
Upload web files:
pio run --target uploadfs
Development
MRJ V2 uses a modular C/C++ architecture.
Most modules use:
module.h
module.cpp
The .h file defines the interface.
The .cpp file contains the implementation.
This structure makes the firmware easier to:
Develop
Debug
Maintain
Expand
Replace hardware drivers
Add new modules
Disable unused modules
Configuration Files
Main configuration files:
src/config.h
src/hardware_pinout.h
src/reserved_pins.h
Always verify GPIO assignments before connecting hardware.
Web Interface
Web resources are stored in:
data/
└── index.html
The ESP32 web server can provide a browser-based interface for supported device functions and configuration.
Security Research
MRJ V2 contains modules for educational and authorized security testing, including wireless analysis, BLE analysis, RFID/NFC analysis, infrared diagnostics, and hardware testing.
Only test systems and devices for which you have permission.
Do not use the firmware to interfere with third-party systems, networks, communications, or devices.
Roadmap
[ ] Improved graphical interface
[ ] More display support
[ ] Expanded NFC tools
[ ] Expanded RFID tools
[ ] Additional IR protocols
[ ] Improved BLE diagnostics
[ ] Expanded Sub-GHz diagnostics
[ ] Better SD-card management
[ ] Configuration backup
[ ] Configuration restore
[ ] Improved OTA interface
[ ] Hardware diagnostics
[ ] Module auto-detection
[ ] More system information
Credits
MRJ V2 Team
ESP32 Security & Electronics Toolkit
Disclaimer
MRJ V2 is provided for educational, electronics-development, and authorized security-testing purposes.
The user is responsible for ensuring that their use of the firmware complies with applicable laws, regulations, and permissions.
License
Check the licenses of all third-party libraries used by the project before redistribution.
MRJ V2 Team
�
MRJ V2 Team 

�
ESP32 Security & Electronics Toolkit 
```
