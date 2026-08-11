#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "config.h"
#include "eeprom_manager.h"

class WebServerModule {
public:
    void init();
    void startAP();
    void startServer();
    void stopServer();
    bool isRunning();
    String getIP();
    void setCallback(void (*cb)(String action, String param));

private:
    AsyncWebServer* server = nullptr;
    bool running = false;
    bool apMode = true;
    String currentIP = "";
    void (*actionCallback)(String action, String param) = nullptr;

    void setupRoutes();
    String getStatusJSON();
};

extern WebServerModule webServer;

#endif