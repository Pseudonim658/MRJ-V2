# MRJ_TFT_13_ST7789_240x240

## Spesifikasi
- **Display**: ST7789 240x240 TFT SPI
- **Team A/B Mutex**: AKTIF (TFT)
- **Build Flag**: `-DMRJ_DISPLAY_ST7789_13`

## Cara Compile
1. Install PlatformIO di VS Code
2. Buka folder project ini
3. Pilih environment `esp32dev`
4. Klik Build (centang)
5. Klik Upload (panah)

### Pinout Display TFT ST7789 240x240
| Pin Display | Pin ESP32 | Keterangan |
|-------------|-----------|------------|
| SCK/CLK     | GPIO 18   | VSPI SCK   |
| MISO        | GPIO 19   | VSPI MISO  |
| MOSI/SDA    | GPIO 23   | VSPI MOSI  |
| CS          | GPIO 5    | Chip Select|
| DC/RS       | GPIO 21   | Data/Command|
| RST/RES     | GPIO 22   | Reset      |
| BL/LED      | NC / 3.3V | Backlight  |

> **Team A/B Mutex AKTIF** — CC1101+BadUSB (Team A) dan NFC+RFID (Team B) saling eksklusif.
> VSPI (18/19/23) dibagi dengan CC1101/RFID. Hanya satu tim yang aktif per waktu.

### Pinout Modul Lain (Fixed)
| Modul | Pin ESP32 | Keterangan |
|-------|-----------|------------|
| SD Card (HSPI) | 14(SCK), 26(MISO), 27(MOSI), 4(CS) | File manager |
| NFC PN532 | 16(SDA), 17(SCL) | I2C (0x24) |
| IR Receiver | GPIO 36 | Input      |
| IR Transmitter | GPIO 12 | Output     |
| iButton | GPIO 2 | OneWire      |
| Buzzer | GPIO 13 | PWM          |
| Tombol Up | GPIO 32 | Input pullup |
| Tombol Down | GPIO 33 | Input pullup |
| Tombol Select | GPIO 25 | Input pullup |
| Tombol Back | GPIO 34 | Input pullup |
| Baterai ADC | GPIO 37 | Analog     |

### Pinout Modul Optional
| Modul | Pin | Keterangan |
|-------|-----|------------|
| CC1101 | CS=-1 (disabled) | Aktif via Module Control (Team A) |
| RFID | CS=-1 (disabled) | Aktif via Module Control (Team B) |
| BadUSB CH9326 | TX=-1, RX=-1 | Aktif via Module Control (Team A) |
| RFID 125kHz | RX=-1, TX=-1 | Disabled |
