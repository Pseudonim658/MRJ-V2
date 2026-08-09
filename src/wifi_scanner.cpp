#include "wifi_scanner.h"

WiFiScanner wifiScanner;

int WiFiScanner::scan() {
    WiFi.scanDelete();
    int n = WiFi.scanNetworks();
    networks.clear();
    for (int i = 0; i < n; i++) {
        WiFiDetail d;
        d.ssid = WiFi.SSID(i);
        memcpy(d.bssid, WiFi.BSSID(i), 6);
        d.channel = WiFi.channel(i);
        d.rssi = WiFi.RSSI(i);
        uint8_t encType = WiFi.encryptionType(i);
        d.encryption = getEncryptionString(encType);
        networks.push_back(d);
    }
    WiFi.scanDelete();
    logger.log(LOG_INFO, "WIFI_SCAN", ("Found " + String(n) + " networks").c_str());
    return n;
}

int WiFiScanner::getCount() { return networks.size(); }
WiFiDetail* WiFiScanner::getNetworks() { return networks.data(); }

String WiFiScanner::getEncryptionString(uint8_t type) {
    switch (type) {
        case WIFI_AUTH_OPEN: return "OPEN";
        case WIFI_AUTH_WEP: return "WEP";
        case WIFI_AUTH_WPA_PSK: return "WPA";
        case WIFI_AUTH_WPA2_PSK: return "WPA2";
        case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
        case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-ENT";
        default: return "UNKNOWN";
    }
}

String WiFiScanner::bssidToString(uint8_t* bssid) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
    return String(buf);
}
