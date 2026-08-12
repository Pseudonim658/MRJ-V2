#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "sd_card.h"
#include "config.h"

enum LogLevel { LOG_INFO, LOG_WARN, LOG_ERROR, LOG_CAPTURE };

class LoggerModule {
public:
    void init();
    void log(LogLevel level, const char* module, const char* message);
    void log(LogLevel level, const char* module, const String& message) { log(level, module, message.c_str()); }
    void logf(LogLevel level, const char* module, const char* fmt, ...);
    void logCapture(const char* module, const char* data);
    void setAutoLog(bool en);
    bool isAutoLog();
    String getTimestamp();
    String getLogs(int count = 20);
    void clearLogs();

private:
    bool autoLog = true;
    unsigned long bootTime = 0;
    String levelStr(LogLevel level);
};

extern LoggerModule logger;

#endif
