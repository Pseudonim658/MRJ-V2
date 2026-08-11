#include "rfid_125khz.h"

RFID125kHz rfid125;

void RFID125kHz::init(uint8_t rxPin, uint8_t txPin) {
    rxPin_ = rxPin;
    txPin_ = txPin;
    if (rxPin_ == (uint8_t)-1 || rxPin_ > 39) {
        logger.log(LOG_WARN, "RFID125", "Pins disabled");
        return;
    }
    Serial2.begin(9600, SERIAL_8N1, rxPin_, txPin_);
    readBuffer = "";
    lastCard.uidStr = "";
    lastCard.type = "";
    memset(lastCard.uid, 0, sizeof(lastCard.uid));
    logger.log(LOG_INFO, "RFID125", "125kHz reader ready");
}

bool RFID125kHz::readCard() {
    while (Serial2.available()) {
        char c = Serial2.read();
        if (c == '\r' || c == '\n') {
            if (readBuffer.length() >= 8) {
                String cleaned = parseUID(readBuffer);
                if (cleaned.length() >= 8) {
                    lastCard.uidStr = cleaned;
                    lastCard.type = (cleaned.length() == 10) ? "EM4100" : "GENERIC";
                    // fill raw bytes if possible
                    int bytes = min(5, (int)(cleaned.length() / 2));
                    for (int i = 0; i < bytes; i++) {
                        lastCard.uid[i] = strtol(cleaned.substring(i*2, i*2+2).c_str(), NULL, 16);
                    }
                    logger.logCapture("RFID125", ("UID: " + lastCard.uidStr + " [" + lastCard.type + "]").c_str());
                    buzzer.success();
                    readBuffer = "";
                    return true;
                }
            }
            readBuffer = "";
        } else if (isPrintable(c) && readBuffer.length() < 64) {
            readBuffer += c;
        }
    }
    return false;
}

String RFID125kHz::parseUID(String data) {
    data.trim();
    String cleaned = "";
    for (unsigned i = 0; i < data.length(); i++) {
        char ch = data.charAt(i);
        if (isxdigit(ch)) cleaned += (char)toupper(ch);
    }
    return cleaned;
}

RFID125Card RFID125kHz::getLastCard() { return lastCard; }
