#include "logger.h"

LoggerModule logger;

void LoggerModule::init() {
    bootTime = millis();
    autoLog = true;
    log(LOG_INFO, "SYS", "Logger initialized");
}

String LoggerModule::getTimestamp() {
    unsigned long elapsed = millis() - bootTime;
    unsigned long secs = elapsed / 1000;
    unsigned long mins = secs / 60;
    unsigned long hrs = mins / 60;
    char buf[20];
    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu", hrs, mins % 60, secs % 60);
    return String(buf);
}

String LoggerModule::levelStr(LogLevel level) {
    switch (level) {
        case LOG_INFO: return "INFO";
        case LOG_WARN: return "WARN";
        case LOG_ERROR: return "ERR ";
        case LOG_CAPTURE: return "CAP ";
        default: return "????";
    }
}

void LoggerModule::log(LogLevel level, const char* module, const char* message) {
    String ts = getTimestamp();
    String entry = "[" + ts + "][" + levelStr(level) + "][" + String(module) + "] " + String(message) + "\n";
    Serial.print(entry);
    if (autoLog && sdCard.isReady()) {
        String path = String(SD_LOG_DIR) + "/log.txt";
        sdCard.appendFile(path.c_str(), entry.c_str());
    }
}

void LoggerModule::logCapture(const char* module, const char* data) {
    String ts = getTimestamp();
    String entry = "[" + ts + "][" + String(module) + "] " + String(data) + "\n";
    Serial.print("[CAPTURE] " + entry);
    if (sdCard.isReady()) {
        String path = String(SD_CAPTURE_DIR) + "/" + String(module) + "_captures.txt";
        sdCard.appendFile(path.c_str(), entry.c_str());
    }
}

void LoggerModule::setAutoLog(bool en) { autoLog = en; }
bool LoggerModule::isAutoLog() { return autoLog; }

String LoggerModule::getLogs(int count) {
    if (!sdCard.isReady()) return "SD Card not ready";
    String path = String(SD_LOG_DIR) + "/log.txt";
    return sdCard.getLogs(path.c_str(), count);
}

void LoggerModule::clearLogs() {
    if (sdCard.isReady()) {
        String path = String(SD_LOG_DIR) + "/log.txt";
        sdCard.deleteFile(path.c_str());
    }
}
