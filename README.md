# MRJ V2 — Universal Display Firmware (13 Variants)

Firmware ESP32 all-in-one untuk pengujian keamanan nirkabel.

## 13 Varian Display

### TFT (Team A/B Mutex AKTIF)
| Varian | Display | Resolusi | Bus |
|--------|---------|----------|-----|
| TFT_18_ST7735_128x160 | ST7735 | 128×160 | SPI |
| TFT_13_ST7789_240x240 | ST7789 | 240×240 | SPI |
| TFT_154_ST7789_240x240 | ST7789 | 240×240 | SPI |
| TFT_20_ST7789_240x320 | ST7789 | 240×320 | SPI |
| TFT_24_ST7789_240x320 | ST7789 | 240×320 | SPI |
| TFT_24_ILI9341_240x320 | ILI9341 | 240×320 | SPI |
| TFT_28_ILI9341_240x320 | ILI9341 | 240×320 | SPI |
| TFT_35_ILI9488_320x480 | ILI9488 | 320×480 | SPI |

### OLED (Team A/B Mutex NON-AKTIF)
| Varian | Display | Resolusi | Bus |
|--------|---------|----------|-----|
| OLED_096_SSD1306_128x64 | SSD1306 | 128×64 | I2C |
| OLED_13_SSD1306_128x64 | SSD1306 | 128×64 | I2C |
| OLED_15_SH1106_128x64 | SH1106 | 128×64 | I2C |
| OLED_20_SSD1306_128x64 | SSD1306 | 128×64 | I2C |
| OLED_242_SH1106_128x64 | SH1106 | 128×64 | I2C |

## Pinout

### Fixed (Semua Varian)
- SD Card: GPIO 14/26/27/4 (HSPI)
- NFC: GPIO 16/17 (I2C)
- IR: GPIO 36/12
- iButton: GPIO 2
- Buzzer: GPIO 13
- Tombol: GPIO 32/33/25/34

### TFT Display
- SCK: GPIO 18, MISO: GPIO 19, MOSI: GPIO 23
- CS: GPIO 5, DC: GPIO 21, RST: GPIO 22

### OLED Display
- SDA: GPIO 16, SCL: GPIO 17 (shared NFC)

### Modul Optional
- **TFT**: Team A/B mutex (CC1101+BadUSB vs NFC+RFID)
- **OLED**: NO mutex, semua modul bisa aktif bersama

## Cara Compile
1. Buka folder varian di VS Code + PlatformIO
2. Pilih environment `esp32dev`
3. Build & Upload

## Lisensi
MIT License
