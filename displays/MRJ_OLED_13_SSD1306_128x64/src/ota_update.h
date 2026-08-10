#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <Arduino.h>
#include <WiFi.h>
#include <Update.h>
#include <ESPAsyncWebServer.h>
#include "config.h"
#include "logger.h"

class OTAUpdate {
public:
    void init();
    void update();
    void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

private:
    bool otaRunning = false;
};

extern OTAUpdate ota;

#endif