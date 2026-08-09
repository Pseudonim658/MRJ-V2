#include "badusb.h"
#include "sd_card.h"

BadUSBModule badUSB;

void BadUSBModule::init() {
    if (CH9326_RX < 0 || CH9326_TX < 0) {
        logger.log(LOG_WARN, "BADUSB", "BadUSB disabled (pins -1)");
        return;
    }
    serial_.begin(9600, SERIAL_8N1, CH9326_RX, CH9326_TX);
    running = false;
    logger.log(LOG_INFO, "BADUSB", "BadUSB initialized on Serial2");
}

void BadUSBModule::typeString(const char* str) {
    if (!running) return;
    while (*str) {
        uint8_t key = 0;
        uint8_t shift = 0;
        char c = *str;

        if (c >= 'A' && c <= 'Z') {
            key = 0x04 + (c - 'A');
            shift = 0x02;
        } else if (c >= 'a' && c <= 'z') {
            key = 0x04 + (c - 'a');
        } else if (c >= '0' && c <= '9') {
            key = 0x1E + (c - '0');
        } else if (c == ' ') {
            key = 0x2C;
        } else if (c == '\n') {
            pressKey(0x28);
            releaseKey();
            str++;
            continue;
        } else {
            str++;
            continue;
        }

        uint8_t report[8] = {0};
        report[0] = shift;
        report[2] = key;
        serial_.write(0x57);
        serial_.write(0xAB);
        serial_.write(8);
        serial_.write(report, 8);
        delay(10);
        uint8_t empty[8] = {0};
        serial_.write(0x57);
        serial_.write(0xAB);
        serial_.write(8);
        serial_.write(empty, 8);
        delay(5);
        str++;
    }
}

void BadUSBModule::pressKey(uint8_t key) {
    uint8_t report[8] = {0};
    report[2] = key;
    serial_.write(0x57);
    serial_.write(0xAB);
    serial_.write(8);
    serial_.write(report, 8);
}

void BadUSBModule::releaseKey() {
    uint8_t empty[8] = {0};
    serial_.write(0x57);
    serial_.write(0xAB);
    serial_.write(8);
    serial_.write(empty, 8);
}

void BadUSBModule::executeScript(const char* script) {
    running = true;
    logger.log(LOG_INFO, "BADUSB", "Executing script...");
    buzzer.click();

    String s = String(script);
    int start = 0;
    while (start < s.length() && running) {
        int end = s.indexOf('\n', start);
        if (end == -1) end = s.length();
        String line = s.substring(start, end);
        line.trim();
        if (line.length() > 0) {
            processLine(line.c_str());
        }
        start = end + 1;
    }
    running = false;
    buzzer.success();
    logger.log(LOG_INFO, "BADUSB", "Script completed");
}

void BadUSBModule::executeFromSD(const char* filename) {
    if (!sdCard.isReady()) {
        logger.log(LOG_ERROR, "BADUSB", "SD Card not ready");
        return;
    }
    String content = sdCard.readFile(filename);
    if (content.length() > 0) {
        executeScript(content.c_str());
    }
}

void BadUSBModule::processLine(const char* line) {
    String l = String(line);
    if (l.startsWith("STRING ")) {
        typeString(l.substring(7).c_str());
    } else if (l.startsWith("DELAY ")) {
        int d = l.substring(6).toInt();
        delay(d);
    } else if (l == "ENTER") {
        pressKey(0x28);
        delay(10);
        releaseKey();
    } else if (l.startsWith("REM ")) {
        // Comment
    } else {
        logger.log(LOG_WARN, "BADUSB", ("Unknown: " + l).c_str());
    }
}

void BadUSBModule::stop() { 
    running = false; 
    serial_.end();
    pinMode(CH9326_TX, INPUT);
    pinMode(CH9326_RX, INPUT);
}
bool BadUSBModule::isRunning() { return running; }
