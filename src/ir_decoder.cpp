#include "ir_decoder.h"

IRDecoder irDecoder;

void IRDecoder::init() {
    pinMode(IR_RECV_PIN, INPUT);
    rawLen = 0;
    recording = true;
    lastPulse = micros();
    logger.log(LOG_INFO, "IR_DECODER", "IR Decoder ready");
}

void IRDecoder::recordPulse() {
    static bool lastState = HIGH;
    bool state = digitalRead(IR_RECV_PIN);
    unsigned long now = micros();
    unsigned long duration = now - lastPulse;

    if (duration > 100000) {
        recording = true;
        rawLen = 0;
        lastPulse = now;
        return;
    }

    if (state != lastState && rawLen < IR_BUFFER_SIZE) {
        rawData[rawLen++] = (uint16_t)duration;
        lastPulse = now;
        lastState = state;
    }
}

bool IRDecoder::decode() {
    recordPulse();
    if (rawLen < 10) return false;

    if (decodeNEC(rawData, rawLen)) return true;
    if (decodeSony(rawData, rawLen)) return true;
    if (decodeRC5(rawData, rawLen)) return true;
    return false;
}

bool IRDecoder::decodeNEC(uint16_t* data, uint16_t len) {
    if (len < 68) return false;
    if (data[0] < 8000 || data[0] > 10000) return false;
    if (data[1] < 4000 || data[1] > 5000) return false;

    uint32_t code = 0;
    for (int i = 2; i < len - 1; i += 2) {
        if (data[i] < 500 || data[i] > 700) return false;
        if (data[i+1] > 1600) {
            code = (code << 1) | 1;
        } else if (data[i+1] > 500) {
            code = (code << 1) | 0;
        } else {
            return false;
        }
    }

    lastSignal.protocol = "NEC";
    lastSignal.address = (code >> 16) & 0xFFFF;
    lastSignal.command = code & 0xFFFF;
    lastSignal.rawLen = len;
    lastSignal.repeat = (code == 0xFFFFFFFF);
    return true;
}

bool IRDecoder::decodeSony(uint16_t* data, uint16_t len) {
    if (len < 24) return false;
    if (data[0] < 2000 || data[0] > 2800) return false;
    if (data[1] < 400 || data[1] > 800) return false;

    uint32_t code = 0;
    for (int i = 2; i < len - 1; i += 2) {
        if (data[i] < 1000 || data[i] > 1400) return false;
        if (data[i+1] > 1200) {
            code = (code << 1) | 1;
        } else if (data[i+1] > 400) {
            code = (code << 1) | 0;
        } else {
            return false;
        }
    }

    lastSignal.protocol = "Sony";
    lastSignal.address = (code >> 8) & 0xFF;
    lastSignal.command = code & 0xFF;
    lastSignal.rawLen = len;
    return true;
}

bool IRDecoder::decodeRC5(uint16_t* data, uint16_t len) {
    if (len < 28) return false;
    if (data[0] < 700 || data[0] > 1000) return false;
    if (data[1] < 700 || data[1] > 1000) return false;

    uint32_t code = 0;
    for (int i = 2; i < len - 1; i += 2) {
        if (data[i] < 700 || data[i] > 1000) return false;
        if (data[i+1] < 700 || data[i+1] > 1000) return false;
        if (data[i] > 800) {
            code = (code << 1) | 1;
        } else {
            code = (code << 1) | 0;
        }
    }

    lastSignal.protocol = "RC5";
    lastSignal.address = (code >> 6) & 0x1F;
    lastSignal.command = code & 0x3F;
    lastSignal.rawLen = len;
    return true;
}

IRDecodedSignal IRDecoder::getLastDecoded() { return lastSignal; }
