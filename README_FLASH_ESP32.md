# MRJ FW V2 - OLED Variants - Siap Compile ke BIN untuk ESP32

## Perbaikan yang sudah diterapkan di source ini:
1. Library `me-no-dev/ESP Async WebServer` diganti ke `esp32async/ESPAsyncWebServer` (package lama sudah tidak tersedia)
2. Library `me-no-dev/AsyncTCP` diganti ke `esp32async/AsyncTCP`
3. `hardware_pinout.h` sekarang include `config.h` agar pin CH9326 dll ter-define
4. Buzzer LEDC API diubah ke classic (`ledcSetup` + `ledcAttachPin`) agar kompatibel
5. Fix const correctness di ch9326.cpp

## Cara Compile jadi BIN (PlatformIO)

### 1. Install tools
- Install VS Code
- Install extension **PlatformIO IDE**
- Atau via CLI: `pip install platformio`

### 2. Build setiap OLED
Buka folder salah satu variant, contoh:

```
cd OLED_096_SSD1306_128x64
pio run
```

Hasil bin ada di:
`.pio/build/esp32dev/firmware.bin`

Juga ada:
- `bootloader.bin`
- `partitions.bin`

### 3. Flash ke ESP32
Gunakan esptool atau PlatformIO Upload:

```
pio run -t upload
```

Atau manual:
```
esptool.py --chip esp32 --port COMx --baud 921600 write_flash \
  0x1000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

### Daftar OLED yang tersedia:
- OLED_096_SSD1306_128x64  (0.96" SSD1306)
- OLED_13_SSD1306_128x64   (1.3" SSD1306)
- OLED_15_SH1106_128x64    (1.5" SH1106)
- OLED_20_SSD1306_128x64   (2.0" SSD1306)
- OLED_242_SH1106_128x64   (2.42" SH1106)

### Pin OLED (semua sama):
- SDA = GPIO 16
- SCL = GPIO 17
- VCC = 3.3V
- GND = GND

### Default WiFi AP:
- SSID: MRJ_AP
- Password: (kosong)
- Web: http://192.168.4.1
- Login: admin / mrj12345

## Catatan
Full binary pre-built tidak bisa dihasilkan di environment ini karena limitasi download package besar & lockfile. 
Gunakan langkah di atas di komputer lokal Anda (Windows/Linux/Mac) — biasanya selesai < 5 menit setelah platform terdownload pertama kali.
