#ifndef BLE_MODULE_H
#define BLE_MODULE_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "config.h"
#include "logger.h"
#include "buzzer.h"

struct BLEDeviceInfo {
    String name;
    String address;
    int rssi;
};

class BLEModule {
public:
    void init();
    void startScan(int duration = 5);
    void stopScan();
    void startSpam();
    void stopSpam();
    bool isScanning();
    bool isSpamming();
    int getDeviceCount();
    BLEDeviceInfo* getDevices();
    void update();

private:
    BLEDeviceInfo devices[30];
    int deviceCount = 0;
    bool scanning = false;
    bool spamming = false;
    unsigned long lastSpam = 0;
    BLEScan* bleScan = nullptr;
};

extern BLEModule bleModule;

#endif
