#include "ota_update.h"

OTAUpdate ota;

void OTAUpdate::init() {
    otaRunning = false;
    logger.log(LOG_INFO, "OTA", "OTA ready");
}

void OTAUpdate::update() {}

void OTAUpdate::handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
        logger.log(LOG_INFO, "OTA", ("Starting OTA update: " + filename).c_str());
        otaRunning = true;
        Update.begin(UPDATE_SIZE_UNKNOWN);
    }

    if (len > 0) {
        Update.write(data, len);
    }

    if (final) {
        if (Update.end(true)) {
            logger.log(LOG_INFO, "OTA", "Update success, restarting...");
            request->send(200, "text/plain", "Update success. Restarting...");
            delay(1000);
            ESP.restart();
        } else {
            logger.log(LOG_ERROR, "OTA", ("Update failed: " + String(Update.getError())).c_str());
            request->send(500, "text/plain", "Update failed");
        }
        otaRunning = false;
    }
}