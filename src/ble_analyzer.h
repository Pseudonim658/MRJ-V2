#ifndef BLE_ANALYZER_H
#define BLE_ANALYZER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <vector>
#include "logger.h"
#include "buzzer.h"

struct BLEDeviceFull {
    String name;
    String address;
    int rssi;
    std::vector<String> uuids;
    String manufacturerData;
};

class BLEAnalyzer {
public:
    void init();
    int scan(int duration = 5);
    int getCount();
    BLEDeviceFull* getDevices();
    void clear();

private:
    std::vector<BLEDeviceFull> devices;
    BLEScan* bleScan = nullptr;
};

extern BLEAnalyzer bleAnalyzer;

#endif
