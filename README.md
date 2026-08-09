MRJ V2 — ESP32 Security & Electronics Toolkit

"MRJ V2" (mrj%20v2.png)

MRJ V2 Team

MRJ V2 adalah firmware berbasis ESP32 DevKit V1 (30-pin) yang menggabungkan berbagai modul elektronik, display, storage, komunikasi, dan fitur pengujian keamanan dalam satu perangkat portabel.

«Educational & authorized security testing only.
Gunakan perangkat hanya pada sistem, jaringan, kartu, dan perangkat yang memang kamu miliki atau memiliki izin untuk menguji.»

---

✨ Fitur Utama

🖥️ Display

- TFT ST7735 1.77" 128×160
- Antarmuka menu berbasis TFT
- Dukungan grafik melalui Adafruit GFX
- Dukungan OLED sebagai display alternatif/cadangan

💾 Storage

- SD Card
- Penyimpanan konfigurasi
- Penyimpanan file/log yang diperlukan firmware
- HSPI dedicated untuk SD Card

📡 NFC

- PN532
- Mode I2C
- Pembacaan NFC/tag yang kompatibel
- IRQ opsional

🆔 RFID

- MFRC522
- RFID 125 kHz EM4100 melalui UART
- Sistem pemilihan modul agar perangkat yang berbagi pin tidak aktif bersamaan

📻 Sub-GHz

- CC1101
- Antarmuka VSPI
- Dukungan fungsi komunikasi/pengujian radio yang sesuai perangkat dan regulasi
- GDO0 tersedia untuk kebutuhan firmware

🔴 Infrared

- IR Receiver
- IR Transmitter
- Receiver menggunakan GPIO 36
- Transmitter menggunakan GPIO 12

🔑 iButton

- Dallas/iButton reader
- 1-Wire
- GPIO 2 sebagai data

🔊 Buzzer

- Buzzer aktif/passif
- PWM melalui GPIO 13
- Dapat digunakan untuk notifikasi suara sederhana

🔘 Tombol

- UP → GPIO 32
- DOWN → GPIO 33
- SELECT → GPIO 25
- BACK → GPIO 34

Sistem tombol menggunakan konsep pull-up dan tombol aktif ketika terhubung ke GND.

🌐 Wi-Fi / Web Interface

- ESP32 Wi-Fi
- Web dashboard
- Access Point
- Konfigurasi melalui browser
- OTA/update support sesuai implementasi firmware

🟦 BLE

- BLE scanning
- Informasi perangkat BLE yang terdeteksi
- Fitur pengujian hanya untuk perangkat/lingkungan yang diizinkan

---

🔌 ESP32 Pinout

Left Side

GPIO| Fungsi
3V3| Power
EN| Reset
GPIO 36| IR Receiver
GPIO 39| Shared UART RX
GPIO 34| BTN BACK
GPIO 35| NFC IRQ
GPIO 32| BTN UP
GPIO 33| BTN DOWN
GPIO 25| BTN SELECT
GPIO 26| SD MISO
GPIO 27| SD MOSI
GPIO 14| SD SCK
GPIO 12| IR Transmitter
GND| Ground
GPIO 13| Buzzer PWM

Right Side

GPIO| Fungsi
GND| Ground
GPIO 23| VSPI MOSI
GPIO 22| TFT RST
GPIO 1| UART0 TX
GPIO 3| Shared control
GPIO 21| TFT DC
GPIO 19| VSPI MISO
GPIO 18| VSPI SCK
GPIO 5| TFT CS
GPIO 17| NFC SCL
GPIO 16| NFC SDA
GPIO 4| SD CS
GPIO 0| Shared CS
GPIO 2| iButton
GPIO 15| Shared UART TX

---

🖥️ TFT ST7735 Wiring

TFT| ESP32
VCC| 3.3V
GND| GND
SCK| GPIO 18
MISO| GPIO 19
MOSI| GPIO 23
CS| GPIO 5
DC| GPIO 21
RST| GPIO 22
LED/BL| 3.3V / sesuai modul

«⚠️ Periksa spesifikasi modul TFT sebelum memberikan tegangan. Jangan mengasumsikan semua breakout memiliki input 5V yang aman.»

---

💾 SD Card Wiring

SD| ESP32
GND| GND
SCK| GPIO 14
MISO| GPIO 26
MOSI| GPIO 27
CS| GPIO 4
VCC| Sesuai spesifikasi modul

---

📡 PN532 Wiring

Mode: I2C

PN532| ESP32
VCC| 3.3V / sesuai modul
GND| GND
SDA| GPIO 16
SCL| GPIO 17
IRQ| GPIO 35

Pastikan jumper/switch PN532 diatur ke mode I2C.

---

🔴 IR Wiring

Receiver

Receiver| ESP32
VCC| 3.3V
GND| GND
OUT| GPIO 36

Transmitter

GPIO 12 digunakan sebagai output transmitter. Untuk LED IR berarus lebih tinggi, gunakan driver transistor yang sesuai.

---

🔑 iButton

iButton| ESP32
DATA| GPIO 2
GND| GND
VCC| Sesuai metode/modul

GPIO 2 digunakan sebagai jalur 1-Wire.

---

🔊 Buzzer

Buzzer| ESP32
+| GPIO 13
-| GND

Untuk buzzer yang membutuhkan arus lebih besar, gunakan transistor driver.

---

🔘 Button Pinout

Button| GPIO
UP| 32
DOWN| 33
SELECT| 25
BACK| 34

---

⚔️ Shared Pin Architecture

MRJ V2 memiliki beberapa modul yang berbagi jalur GPIO.

Team A

- CC1101
- CH9326

Team B

- PN532
- MFRC522
- RFID 125 kHz

Pin yang digunakan bersama antara beberapa modul perlu dikelola firmware sehingga perangkat yang tidak digunakan dilepas dari jalur GPIO.

Shared GPIO:

GPIO 0
GPIO 3
GPIO 15
GPIO 39

Konsep ini mencegah dua peripheral mencoba mengendalikan jalur yang sama secara bersamaan.

---

📚 Library

PlatformIO

Library yang digunakan/diperlukan antara lain:

olikraus/U8g2
adafruit/Adafruit GFX Library
adafruit/Adafruit ST7735 and ST7789 Library
adafruit/Adafruit ILI9341
adafruit/Adafruit ILI9488
bblanchon/ArduinoJson
me-no-dev/AsyncTCP
me-no-dev/ESP Async WebServer

Library ESP32/Arduino yang digunakan:

WiFi
SPI
Wire
EEPROM
SD
Update
BLEDevice
HardwareSerial

---

📁 Project Structure

mrj_v2-/
│
├── README.md
├── mrj v2.png
├── platformio.ini
│
├── src/
│   ├── MRJ_FW_V2.ino
│   ├── config.h
│   ├── hardware_pinout.h
│   ├── reserved_pins.h
│   │
│   ├── display.h
│   ├── display.cpp
│   │
│   ├── eeprom.h
│   ├── eeprom.cpp
│   │
│   ├── wifi/
│   ├── nfc/
│   ├── rfid/
│   ├── cc1101/
│   ├── ir/
│   ├── ibutton/
│   ├── sd/
│   ├── ble/
│   └── web/
│
└── lib/
    └── README.md

«Struktur aktual dapat berbeda tergantung versi firmware yang berada di repository.»

---

⚙️ PlatformIO Configuration

Board utama:

ESP32 DevKit V1

Framework:

Arduino

Contoh environment:

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_speed = 921600

---

🚀 Installation

1. Clone repository

git clone https://github.com/j42844343-byte/mrj_v2-.git
cd mrj_v2-

2. Buka project

Buka folder project menggunakan PlatformIO/VS Code.

3. Hubungkan ESP32

Hubungkan ESP32 DevKit V1 melalui USB.

4. Build

Jalankan:

pio run

5. Upload

Jalankan:

pio run -t upload

6. Serial Monitor

pio device monitor

---

📸 Hardware Reference

Gambar pinout dan wiring utama:

mrj v2.png

File gambar harus berada di root repository agar README dapat menampilkannya.

---

🛠️ Development

MRJ V2 dikembangkan sebagai project elektronik/embedded untuk:

- Eksperimen ESP32
- Pembelajaran GPIO
- SPI
- I2C
- UART
- 1-Wire
- TFT display
- SD Card
- NFC/RFID
- Infrared
- BLE
- Wi-Fi
- Integrasi berbagai modul hardware

---

⚠️ Safety & Responsible Use

MRJ V2 dapat berinteraksi dengan berbagai sistem radio, kartu, tag, USB/HID, dan jaringan.

Gunakan hanya:

- perangkat milik sendiri;
- jaringan/lab yang memang kamu punya izin untuk uji;
- tag/kartu yang memang kamu miliki atau diizinkan untuk diuji;
- frekuensi radio sesuai aturan setempat.

Jangan digunakan untuk mengakses, mengganggu, atau mengambil data dari perangkat orang lain tanpa izin.

---

👥 MRJ V2 Team

MRJ V2 Team

Embedded Systems • ESP32 • Electronics • Security Research

---

📄 License

Tambahkan license yang sesuai dengan keputusan pengembang project ini.

---

⭐ MRJ V2

ESP32-based modular electronics & security testing platform

MRJ V2
ESP32 DevKit V1
TFT + SD + NFC + RFID + IR + iButton + BLE + Wi-Fi

Created by MRJ V2 Team
