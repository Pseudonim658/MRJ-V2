#include "ble_module.h"

BLEModule bleModule;

void BLEModule::init() {
    BLEDevice::init("MRJ_BLE");
    bleScan = BLEDevice::getScan();
    bleScan->setActiveScan(true);
    bleScan->setInterval(100);
    bleScan->setWindow(99);
    logger.log(LOG_INFO, "BLE", "BLE initialized");
}

void BLEModule::startScan(int duration) {
    scanning = true;
    deviceCount = 0;
    BLEScanResults results = bleScan->start(duration, false);
    int count = results.getCount();
    deviceCount = min(count, 30);
    for (int i = 0; i < deviceCount; i++) {
        BLEAdvertisedDevice d = results.getDevice(i);
        devices[i].name = d.haveName() ? String(d.getName().c_str()) : "Unknown";
        devices[i].address = String(d.getAddress().toString().c_str());
        devices[i].rssi = d.getRSSI();
    }
    bleScan->clearResults();
    scanning = false;
    logger.log(LOG_INFO, "BLE", ("Scan found " + String(deviceCount) + " devices").c_str());
    buzzer.success();
}

void BLEModule::stopScan() {
    bleScan->stop();
    scanning = false;
}

void BLEModule::startSpam() {
    spamming = true;
    lastSpam = 0;
    logger.log(LOG_INFO, "BLE", "BLE spam started");
    buzzer.beep(1500, 100);
}

void BLEModule::stopSpam() {
    spamming = false;
    BLEDevice::getAdvertising()->stop();
    logger.log(LOG_INFO, "BLE", "BLE spam stopped");
    buzzer.click();
}

bool BLEModule::isScanning() { return scanning; }
bool BLEModule::isSpamming() { return spamming; }
int BLEModule::getDeviceCount() { return deviceCount; }
BLEDeviceInfo* BLEModule::getDevices() { return devices; }

void BLEModule::update() {
    if (!spamming) return;
    if (millis() - lastSpam < 100) return;
    lastSpam = millis();

    BLEAdvertising* adv = BLEDevice::getAdvertising();
    adv->stop();

    BLEAdvertisementData advData;
    uint8_t rnd[6];
    for (int i = 0; i < 6; i++) rnd[i] = random(0, 255);
    String fakeName = "Device_" + String(rnd[0], HEX) + String(rnd[1], HEX);
    advData.setName(fakeName.c_str());
    adv->setAdvertisementData(advData);
    adv->start();
}
