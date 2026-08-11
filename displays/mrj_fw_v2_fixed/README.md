# MRJ Firmware V2

## Deskripsi
MRJ V2 adalah firmware ESP32 all-in-one untuk pengujian keamanan nirkabel, IoT, dan kontrol hardware.

## Fitur
- **Display**: ST7735 TFT 1.77" 128x160 (bisa diubah ke OLED)
- **WiFi Deauth & Nethercap**: Evil Twin, Captive Portal, Deauth Attack
- **BLE**: Scanner, Spam, Transfer
- **Sub-GHz**: CC1101 (315/433/868/915 MHz)
- **RFID & NFC**: Baca, Clone, Emulate
- **iButton**: Baca, Emulate
- **IR**: Record, Play, Decode (NEC/Sony/RC5)
- **BadUSB**: CH9326 HID Keyboard
- **GPIO Control**: Kontrol pin dari web
- **SD Card**: File manager, logging, script storage
- **Web Dashboard**: Full control dari browser
- **OTA Update**: Update firmware dari web
- **Module Control**: Aktif/nonaktifkan modul tanpa restart

## Hardware
- ESP32 DevKit V1 (30-pin)
- ST7735 TFT 1.77" 128x160
- SD Card (HSPI)
- NFC PN532 (I2C)
- IR Receiver & Transmitter
- iButton (OneWire)
- CC1101 (Sub-GHz) - opsional
- RFID MFRC522 - opsional
- CH9326 (BadUSB) - opsional

## Cara Compile
1. Install PlatformIO di VS Code
2. Buka folder project
3. Pilih environment `esp32dev`
4. Klik Build (centang)
5. Klik Upload (panah)

## Cara Pakai
1. Connect ke WiFi `MRJ_AP` (password kosong)
2. Buka `192.168.4.1`
3. Login dengan `admin` / `mrj12345`
4. Aktifkan modul di Module Control
5. Gunakan fitur sesuai kebutuhan

## Lisensi
MIT