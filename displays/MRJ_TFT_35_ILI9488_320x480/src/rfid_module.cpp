#include "rfid_module.h"

RFIDModule rfidModule;

void RFIDModule::init() { begin(); }

void RFIDModule::begin() {
    if (initialized) return;
    if (RFID_CS < 0) {
        logger.log(LOG_WARN, "RFID", "RFID disabled (CS pin -1)");
        return;
    }
    // MFRC522 would be initialized here
    initialized = true;
    logger.log(LOG_INFO, "RFID", "RFID module initialized (stub)");
}

void RFIDModule::end() {
    initialized = false;
}

bool RFIDModule::readCard() {
    if (!initialized) return false;
    logger.log(LOG_INFO, "RFID", "Read card attempted (stub)");
    return false;
}

void RFIDModule::saveCard() {
    if (savedCount < 20 && lastCard.uidLen > 0) {
        savedCards[savedCount] = lastCard;
        savedCount++;
        buzzer.success();
    }
}

int RFIDModule::getSavedCount() { return savedCount; }
RFIDTag* RFIDModule::getSavedCards() { return savedCards; }
RFIDTag RFIDModule::getLastCard() { return lastCard; }
void RFIDModule::clearSaved() { savedCount = 0; }