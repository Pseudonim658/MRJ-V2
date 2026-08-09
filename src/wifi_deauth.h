#ifndef WIFI_DEAUTH_H
#define WIFI_DEAUTH_H

#include <Arduino.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "config.h"
#include "logger.h"
#include "buzzer.h"

struct WiFiNetwork {
    String ssid;
    uint8_t bssid[6];
    int32_t rssi;
    uint8_t channel;
    bool selected;
};

class WiFiDeauthModule {
public:
    void init();
    int scanNetworks();
    void startDeauth(int targetIdx);
    void startDeauthAll();
    void stopDeauth();
    bool isActive();
    unsigned long getFrameCount();
    void update();
    WiFiNetwork* getNetworks();
    int getNetworkCount();

private:
    WiFiNetwork networks[20];
    int networkCount = 0;
    bool active = false;
    unsigned long frameCount = 0;
    unsigned long lastFrame = 0;
    int currentTarget = -1;

    void sendDeauthFrame(uint8_t* bssid, uint8_t channel);
};

extern WiFiDeauthModule wifiDeauth;

#endif
