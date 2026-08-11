# MRJ Firmware V2 — All 14 Variants (Fixed + GitHub Actions)

## Cara pakai

1. Extract ZIP ini
2. Isi folder `displays/` **timpa** ke folder `displays/` di repo GitHub kamu
3. Copy folder `.github/` ke root repo (timpa yang lama)
4. Commit & push ke `main`
5. Buka tab **Actions** → tunggu build selesai
6. Download artifact **MRJ_FW_V2_ALL_BINS**

## Yang sudah di-fix (agar compile lulus)

- `buzzer.cpp` → classic LEDC (`ledcSetup` + `ledcAttachPin`)
- `ch9326.cpp` → const-safe `available()`
- `logger` → support printf-style (`log(level, module, fmt, ...)`)
- Library Async → `esp32async/AsyncTCP` + `esp32async/ESPAsyncWebServer`
- `hardware_pinout.h` include `config.h`

## Variant (14)

### OLED
- MRJ_OLED_096_SSD1306_128x64
- MRJ_OLED_13_SSD1306_128x64
- MRJ_OLED_15_SH1106_128x64
- MRJ_OLED_20_SSD1306_128x64
- MRJ_OLED_242_SH1106_128x64

### TFT
- MRJ_TFT_13_ST7789_240x240
- MRJ_TFT_154_ST7789_240x240
- MRJ_TFT_18_ST7735_128x160
- MRJ_TFT_20_ST7789_240x320
- MRJ_TFT_24_ILI9341_240x320
- MRJ_TFT_24_ST7789_240x320
- MRJ_TFT_28_ILI9341_240x320
- MRJ_TFT_35_ILI9488_320x480

### Base
- MRJ_FW_V2_FIXED

## Flash
```bash
esptool.py --chip esp32 --port COMx --baud 921600 write_flash \
  0x1000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

Default AP: `MRJ_AP` (tanpa password) → http://192.168.4.1 → admin / mrj12345
