#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <Arduino.h>
#include <WiFi.h>
#include <vector>
#include "logger.h"

struct WiFiDetail {
    String ssid;
    uint8_t bssid[6];
    int channel;
    int rssi;
    String encryption;
};

class WiFiScanner {
public:
    int scan();
    int getCount();
    WiFiDetail* getNetworks();
    String getEncryptionString(uint8_t type);
    String bssidToString(uint8_t* bssid);

private:
    std::vector<WiFiDetail> networks;
};

extern WiFiScanner wifiScanner;

#endif