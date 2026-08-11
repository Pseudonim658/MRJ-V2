# MRJ_OLED_242_SH1106_128x64

## Spesifikasi
- **Display**: SH1106 128x64 OLED I2C
- **Team A/B Mutex**: NON-AKTIF (OLED)
- **Build Flag**: `-DMRJ_DISPLAY_SH1106_242`

## Cara Compile
1. Install PlatformIO di VS Code
2. Buka folder project ini
3. Pilih environment `esp32dev`
4. Klik Build (centang)
5. Klik Upload (panah)

### Pinout Display OLED SH1106 128x64
| Pin Display | Pin ESP32 | Keterangan |
|-------------|-----------|------------|
| SDA         | GPIO 16   | I2C SDA (shared with NFC) |
| SCL         | GPIO 17   | I2C SCL (shared with NFC) |
| VCC         | 3.3V      | Power      |
| GND         | GND       | Ground     |
| RST (opt)   | NC        | Reset (jika ada) |

> **Team A/B Mutex NON-AKTIF** — Semua modul (CC1101, RFID, BadUSB, NFC) bisa aktif bersamaan!
> VSPI (18/19/23) bebas untuk CC1101 (CS=5) dan RFID (CS=15, RST=21).

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
| Modul | Pin ESP32 | Keterangan |
|-------|-----------|------------|
| CC1101 | CS=5, GDO0=-1, GDO2=-1 | Aktif via Module Control |
| RFID 13.56MHz | CS=15, RST=21 | Aktif via Module Control |
| BadUSB CH9326 | TX=22, RX=35 | Aktif via Module Control |
| RFID 125kHz | RX=39, TX=-1 | Optional (input-only OK) |
