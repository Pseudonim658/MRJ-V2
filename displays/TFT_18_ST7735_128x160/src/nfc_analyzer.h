#ifndef NFC_ANALYZER_H
#define NFC_ANALYZER_H

#include <Arduino.h>
#include "nfc_module.h"

struct NFCTagDetail {
    String uid;
    String type;
    String technology;
    uint8_t atqa[2];
    uint8_t sak;
};

class NFCAnalyzer {
public:
    void init();
    bool readTag();
    NFCTagDetail getLastTag();

private:
    NFCTagDetail lastTag;
};

extern NFCAnalyzer nfcAnalyzer;

#endif