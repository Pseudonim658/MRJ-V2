#include "ota_update.h"

OTAUpdate ota;

void OTAUpdate::init() {
    otaRunning = false;
    logger.log(LOG_INFO, "OTA", "OTA ready (web upload)");
}

void OTAUpdate::update() {
    // Reserved for future progress / watchdog
}

void OTAUpdate::handleUpload(AsyncWebServerRequest *request, String filename,
                             size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
        logger.log(LOG_INFO, "OTA", ("Starting OTA: " + filename).c_str());
        otaRunning = true;

        if (Update.isRunning()) {
            Update.abort();
        }

        if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH)) {
            logger.log(LOG_ERROR, "OTA", ("begin failed: " + String(Update.getError())).c_str());
            request->send(500, "text/plain", "OTA begin failed");
            otaRunning = false;
            return;
        }
    }

    if (len > 0) {
        size_t written = Update.write(data, len);
        if (written != len) {
            logger.log(LOG_ERROR, "OTA", "Write mismatch");
            Update.abort();
            request->send(500, "text/plain", "OTA write error");
            otaRunning = false;
            return;
        }
    }

    if (final) {
        if (Update.end(true)) {
            logger.log(LOG_INFO, "OTA", "Update success, restarting in 1.5s...");
            request->send(200, "text/plain", "OK - Update success. Device will reboot.");
            delay(1500);
            ESP.restart();
        } else {
            String err = "Update failed: " + String(Update.getError());
            logger.log(LOG_ERROR, "OTA", err.c_str());
            request->send(500, "text/plain", err);
        }
        otaRunning = false;
    }
}
