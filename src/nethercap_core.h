#ifndef NETHERCAP_CORE_H
#define NETHERCAP_CORE_H

#include <Arduino.h>
#include <WiFi.h>
#include <vector>
#include "config.h"
#include "logger.h"
#include "buzzer.h"
#include "sd_card.h"
#include "eeprom_manager.h"

struct Target {
    String ssid;
    uint8_t bssid[6];
    int channel;
    int rssi;
    bool selected;
    unsigned long lastDeauth;
    unsigned int deauthCount;
};

struct Credential {
    String ssid;
    String password;
    String bssid;
    String timestamp;
};

class NethercapCore {
public:
    void init();
    void start();
    void stop();
    void update();
    bool isRunning();

    void startDeauthSelected();
    void stopDeauth();
    bool isDeauthRunning();
    unsigned long getTotalDeauthFrames();

    int scanNetworks();
    int getTargetCount();
    Target* getTargets();
    void selectTarget(int index);
    void deselectTarget(int index);
    void selectAllTargets();
    void deselectAllTargets();
    void setTargetSSID(const char* ssid);

    void startRogueAP(const char* targetSSID = nullptr);
    void stopRogueAP();
    bool isRogueAPActive();
    String getRogueAPSSID();
    int getConnectedClients();

    int getCredentialCount();
    Credential* getCredentials();
    void clearCredentials();
    bool exportCredentials(const char* filename);

    void startBeaconSpam();
    void stopBeaconSpam();
    bool isBeaconSpamActive();

    String getIndexHTML();
    String getLoginHTML();

private:
    bool running = false;
    bool deauthRunning = false;
    bool rogueAPActive = false;
    bool beaconSpamActive = false;

    std::vector<Target> targets;
    int selectedTargetCount = 0;

    std::vector<Credential> credentials;

    unsigned long lastDeauthFrame = 0;
    int deauthInterval = 10;
    unsigned long totalDeauthFrames = 0;

    unsigned long lastBeaconSpam = 0;
    int beaconSpamInterval = 100;

    String rogueSSID = "";
    String targetSSID = "";

    void sendDeauthFrame(uint8_t* bssid, uint8_t channel);
    void sendBeaconFrame(const char* ssid, uint8_t channel, uint8_t* bssid);
    void processCredential(String ssid, String pass, String bssid);

    String bssidToString(uint8_t* bssid);
    void randomMac(uint8_t* mac);
};

extern NethercapCore nethercap;

#endif
