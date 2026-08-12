# MRJ FW V2 — ESP32 Firmware Collection

Repository resmi firmware **MRJ FW V2** untuk ESP32. Proyek ini mendukung 14 varian display yang terbagi menjadi **5 varian OLED** (dengan source code lengkap di repository) dan **9 varian TFT** (dengan paket source ZIP tersendiri dan sistem eksklusif Team A/B).

## Struktur Repository

- `oled_variants/` — Berisi source code lengkap (C++/Arduino .ino, headers, modul WiFi, BLE, SubGHz, NFC, WebServer) untuk 5 varian OLED:
  1. `OLED_096_SSD1306_128x64`
  2. `OLED_13_SSD1306_128x64`
  3. `OLED_15_SH1106_128x64`
  4. `OLED_20_SSD1306_128x64`
  5. `OLED_242_SH1106_128x64`

- `tft_source_zips/` — Berisi arsip ZIP source code mandiri untuk 9 varian TFT (menerapkan logika Tim A/B untuk berbagi pin SPI):
  1. `TFT_13_ST7789_240x240_source.zip`
  2. `TFT_154_ST7789_240x240_source.zip`
  3. `TFT_177_ST7735_128x160_source.zip` (Baru!)
  4. `TFT_18_ST7735_128x160_source.zip`
  5. `TFT_20_ST7789_240x320_source.zip`
  6. `TFT_24_ILI9341_240x320_source.zip`
  7. `TFT_24_ST7789_240x320_source.zip`
  8. `TFT_28_ILI9341_240x320_source.zip`
  9. `TFT_35_ILI9488_TFT_eSPI_source.zip`

## Prasyarat Kompilasi
- **Board Package:** ESP32 Arduino Core (v2.0.17 direkomendasikan).
- **Library Pendukung:**
  - `Adafruit GFX Library`
  - `Adafruit SSD1306` & `Adafruit SH110X`
  - `Adafruit ST7735 and ST7789 Library` & `Adafruit ILI9341`
  - `TFT_eSPI` (untuk varian 3.5" ILI9488)
  - `ESPAsyncWebServer` & `AsyncTCP`
  - `ArduinoJson` (v6.x)

## Cara Kompilasi via Arduino CLI
Setiap folder OLED memiliki skrip `compile.sh` untuk memudahkan build. Contoh:
```bash
cd oled_variants/OLED_096_SSD1306_128x64
./compile.sh
```
