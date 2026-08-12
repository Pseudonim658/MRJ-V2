#include "subghz_analyzer.h"
#include "logger.h"

SubGHzAnalyzer subGHzAnalyzer;

void SubGHzAnalyzer::init() {
    subGHz.init();
    logger.log(LOG_INFO, "SUBGHZ_ANALYZER", "Sub-GHz Analyzer ready");
}

void SubGHzAnalyzer::setFrequency(float freq) {
    frequency = freq;
    subGHz.setFrequency(freq);
}

void SubGHzAnalyzer::setModulation(String mod) {
    modulation = mod;
    logger.log(LOG_INFO, "SUBGHZ_ANALYZER", ("Modulation set to: " + mod).c_str());
}

bool SubGHzAnalyzer::receive() {
    subGHz.startReceive();
    delay(500);
    if (subGHz.hasData()) {
        lastSignal.frequency = frequency;
        lastSignal.modulation = modulation;
        lastSignal.rssi = 0;
        lastSignal.dataLen = subGHz.getLastDataLen();
        memcpy(lastSignal.data, subGHz.getLastData(), lastSignal.dataLen);
        subGHz.stopReceive();
        return true;
    }
    subGHz.stopReceive();
    return false;
}

SubGHzSignal SubGHzAnalyzer::getLastSignal() { return lastSignal; }

void SubGHzAnalyzer::freqScan() {
    subGHz.freqScan();
}