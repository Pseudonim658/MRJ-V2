#include "nfc_analyzer.h"

NFCAnalyzer nfcAnalyzer;

void NFCAnalyzer::init() {
    nfcModule.init();
    logger.log(LOG_INFO, "NFC_ANALYZER", "NFC Analyzer ready");
}

bool NFCAnalyzer::readTag() {
    if (!nfcModule.readTag()) return false;
    NFCTag tag = nfcModule.getLastTag();
    lastTag.uid = tag.uidStr;

    if (tag.uidLen == 4) {
        lastTag.type = "MIFARE Classic / Ultralight";
        lastTag.technology = "ISO/IEC 14443 Type A";
    } else if (tag.uidLen == 7) {
        lastTag.type = "MIFARE Desfire / NTAG";
        lastTag.technology = "ISO/IEC 14443 Type A";
    } else if (tag.uidLen == 8) {
        lastTag.type = "FeliCa";
        lastTag.technology = "ISO/IEC 18092 (FeliCa)";
    } else {
        lastTag.type = "Unknown";
        lastTag.technology = "Unknown";
    }
    lastTag.atqa[0] = 0;
    lastTag.atqa[1] = 0;
    lastTag.sak = 0;
    return true;
}

NFCTagDetail NFCAnalyzer::getLastTag() { return lastTag; }