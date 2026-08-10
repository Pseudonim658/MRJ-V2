#include "web_server.h"
#include "nethercap_core.h"
#include "wifi_deauth.h"
#include "logger.h"
#include "buzzer.h"
#include "sd_card.h"
#include "ota_update.h"
#include "gpio_control.h"
#include "reserved_pins.h"

WebServerModule webServer;

void WebServerModule::init() {
    server = new AsyncWebServer(DEFAULT_WEB_PORT);
    running = false;
    currentIP = "";
    logger.log(LOG_INFO, "WEB", "Web server initialized");
}

void WebServerModule::startAP() {
    WiFi.mode(WIFI_AP);
    String ssid = eeprom.getApSsid();
    String pass = eeprom.getApPass();
    if (!eeprom.isApPasswordSet() || pass.length() == 0) {
        WiFi.softAP(ssid.c_str(), NULL);
        logger.log(LOG_INFO, "WEB", ("AP Started (OPEN): " + ssid).c_str());
    } else {
        WiFi.softAP(ssid.c_str(), pass.c_str());
        logger.log(LOG_INFO, "WEB", ("AP Started: " + ssid).c_str());
    }
    currentIP = WiFi.softAPIP().toString();
    apMode = true;
}

void WebServerModule::startServer() {
    if (running) return;
    setupRoutes();
    server->begin();
    running = true;
    logger.log(LOG_INFO, "WEB", "Server started on port " + String(DEFAULT_WEB_PORT));
    buzzer.success();
}

void WebServerModule::stopServer() {
    if (!running) return;
    server->end();
    running = false;
    logger.log(LOG_INFO, "WEB", "Server stopped");
}

bool WebServerModule::isRunning() { return running; }
String WebServerModule::getIP() { return currentIP; }
void WebServerModule::setCallback(void (*cb)(String, String)) { actionCallback = cb; }

void WebServerModule::setupRoutes() {
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<h1>MRJ V2</h1><p>Web server running</p>");
    });

    server->on("/status", HTTP_GET, [this](AsyncWebServerRequest *request){
        request->send(200, "application/json", getStatusJSON());
    });

    server->on("/gpio/toggle", HTTP_POST, [](AsyncWebServerRequest *request){
        if (request->hasParam("pin")) {
            int pin = request->getParam("pin")->value().toInt();
            if (ReservedPinManager::getInstance().isSafeForUser(pin)) {
                gpioControl.togglePin(pin);
                request->send(200, "application/json", "{"state":" + String(digitalRead(pin)) + "}");
            } else {
                request->send(403, "application/json", "{"error":"pin reserved or invalid"}");
            }
        } else {
            request->send(400, "application/json", "{"error":"missing pin"}");
        }
    });

    server->on("/gpio/read", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("pin")) {
            int pin = request->getParam("pin")->value().toInt();
            request->send(200, "application/json", "{"state":" + String(digitalRead(pin)) + "}");
        } else {
            request->send(400, "application/json", "{"error":"missing pin"}");
        }
    });

    server->on("/available_pins", HTTP_GET, [](AsyncWebServerRequest *request){
        StaticJsonDocument<512> doc;
        JsonArray arr = doc.to<JsonArray>();
        for (int pin = 0; pin < 40; pin++) {
            if (ReservedPinManager::getInstance().isSafeForUser(pin)) {
                arr.add(pin);
            }
        }
        String output;
        serializeJson(doc, output);
        request->send(200, "application/json", output);
    });

    server->on("/ota", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "OTA started");
    }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
        ota.handleUpload(request, filename, index, data, len, final);
    });

    server->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not found");
    });
}

String WebServerModule::getStatusJSON() {
    StaticJsonDocument<512> doc;
    doc["running"] = running;
    doc["deauth"] = nethercap.isDeauthRunning();
    doc["rogue"] = nethercap.isRogueAPActive();
    doc["targets"] = nethercap.getTargetCount();
    doc["frames"] = nethercap.getTotalDeauthFrames();
    doc["creds"] = nethercap.getCredentialCount();
    doc["clients"] = nethercap.getConnectedClients();
    doc["ip"] = currentIP;
    doc["version"] = FIRMWARE_VERSION;
    String output;
    serializeJson(doc, output);
    return output;
}