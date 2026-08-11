# MRJ FW V2 - ALL 14 Variants (Fixed Source) - Siap Compile ke BIN ESP32

## Total 14 Variant
### OLED (5)
1. OLED_096_SSD1306_128x64   → 0.96" SSD1306 128x64
2. OLED_13_SSD1306_128x64    → 1.3" SSD1306 128x64
3. OLED_15_SH1106_128x64     → 1.5" SH1106 128x64
4. OLED_20_SSD1306_128x64    → 2.0" SSD1306 128x64
5. OLED_242_SH1106_128x64    → 2.42" SH1106 128x64

### TFT (8)
6. TFT_13_ST7789_240x240
7. TFT_154_ST7789_240x240
8. TFT_18_ST7735_128x160
9. TFT_20_ST7789_240x320
10. TFT_24_ILI9341_240x320
11. TFT_24_ST7789_240x320
12. TFT_28_ILI9341_240x320
13. TFT_35_ILI9488_320x480

### Source utama
14. mrj_fw_v2_fixed

## Perbaikan yang sudah diterapkan:
- Library AsyncTCP & ESPAsyncWebServer diganti ke `esp32async/...` (yang lama sudah hilang)
- hardware_pinout.h include config.h (pin CH9326 dll ter-define)
- Buzzer pakai classic LEDC API (ledcSetup + ledcAttachPin)
- Fix const di ch9326.cpp

## Cara Compile jadi BIN
1. Install PlatformIO (VS Code extension atau `pip install platformio`)
2. Buka folder salah satu variant
3. Jalankan: `pio run`
4. Bin ada di: `.pio/build/esp32dev/firmware.bin`

## Flash
```
pio run -t upload
```
atau esptool:
```
esptool.py --chip esp32 --port COMx --baud 921600 write_flash \
  0x1000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

Default AP: MRJ_AP (tanpa password) → http://192.168.4.1 → admin / mrj12345
