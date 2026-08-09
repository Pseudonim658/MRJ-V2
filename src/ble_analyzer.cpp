#include "ble_analyzer.h"

BLEAnalyzer bleAnalyzer;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {}
};

void BLEAnalyzer::init() {
    // BLEDevice already initialized by bleModule
    bleScan = BLEDevice::getScan();
    bleScan->setActiveScan(true);
    bleScan->setInterval(100);
    bleScan->setWindow(99);
    bleScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    logger.log(LOG_INFO, "BLE_ANALYZER", "BLE Analyzer initialized");
}

int BLEAnalyzer::scan(int duration) {
    devices.clear();
    BLEScanResults results = bleScan->start(duration, false);
    int count = results.getCount();

    for (int i = 0; i < count; i++) {
        BLEAdvertisedDevice d = results.getDevice(i);
        BLEDeviceFull dev;
        dev.name = d.haveName() ? String(d.getName().c_str()) : "Unknown";
        dev.address = String(d.getAddress().toString().c_str());
        dev.rssi = d.getRSSI();

        if (d.haveServiceUUID()) {
            std::string uuidStr = d.getServiceUUID().toString();
            dev.uuids.push_back(String(uuidStr.c_str()));
        }

        if (d.haveManufacturerData()) {
            std::string mfg = d.getManufacturerData();
            dev.manufacturerData = String(mfg.c_str());
        }

        devices.push_back(dev);
    }

    bleScan->clearResults();
    logger.log(LOG_INFO, "BLE_ANALYZER", ("Found " + String(devices.size()) + " BLE devices").c_str());
    return devices.size();
}

int BLEAnalyzer::getCount() { return devices.size(); }
BLEDeviceFull* BLEAnalyzer::getDevices() { return devices.data(); }
void BLEAnalyzer::clear() { devices.clear(); }
