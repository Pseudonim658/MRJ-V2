#include "rfid_125khz.h"

RFID125kHz rfid125;

void RFID125kHz::init(uint8_t rx, uint8_t tx) {
    rxPin_ = rx;
    txPin_ = tx;
    if (rxPin_ < 0 || txPin_ < 0) {
        logger.log(LOG_WARN, "RFID125", "125kHz RFID disabled (pins -1)");
        return;
    }
    Serial1.begin(9600, SERIAL_8N1, rxPin_, txPin_);
    logger.log(LOG_INFO, "RFID125", "125kHz RFID reader initialized on UART");
}

String RFID125kHz::parseUID(String data) {
    if (data.length() < 14) return "";
    String uidHex = data.substring(2, 12);
    String result = "";
    for (int i = 0; i < uidHex.length(); i += 2) {
        if (i > 0) result += ":";
        result += uidHex.substring(i, i+2);
    }
    return result;
}

bool RFID125kHz::readCard() {
    if (rxPin_ < 0) return false;
    while (Serial1.available()) {
        char c = Serial1.read();
        if (c == 0x02) {
            readBuffer = "";
        } else if (c == 0x03) {
            if (readBuffer.length() >= 14) {
                String uid = parseUID(readBuffer);
                if (uid.length() > 0) {
                    lastCard.uidStr = uid;
                    lastCard.type = "EM4100";
                    logger.logCapture("RFID125", ("UID: " + uid).c_str());
                    buzzer.success();
                    return true;
                }
            }
            readBuffer = "";
        } else {
            readBuffer += c;
        }
    }
    return false;
}

RFID125Card RFID125kHz::getLastCard() { return lastCard; }