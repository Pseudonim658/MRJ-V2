#ifndef SD_CARD_H
#define SD_CARD_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <vector>
#include "hardware_pinout.h"
#include "config.h"

class SDCardModule {
public:
    bool init();
    bool isReady();

    bool writeFile(const char* path, const char* data);
    bool appendFile(const char* path, const char* data);
    String readFile(const char* path, size_t maxSize = 4096);

    bool writeBinary(const char* path, uint8_t* data, size_t len);
    bool appendBinary(const char* path, uint8_t* data, size_t len);
    size_t readBinary(const char* path, uint8_t* buffer, size_t maxSize);

    bool deleteFile(const char* path);
    bool renameFile(const char* oldPath, const char* newPath);
    bool copyFile(const char* srcPath, const char* dstPath);
    bool exists(const char* path);
    size_t fileSize(const char* path);

    void listDir(const char* dirname, uint8_t levels, String &output);
    bool createDir(const char* path);
    bool removeDir(const char* path);

    String getLogs(const char* path, int count = 20, size_t maxLineLength = 128);

    uint64_t totalBytes();
    uint64_t usedBytes();
    uint64_t freeBytes();

    String getLastError() { return lastError; }

private:
    bool ready = false;
    String lastError = "";
    SPIClass sdSPI = SPIClass(HSPI);
    String readLine(File &file);
};

extern SDCardModule sdCard;

#endif
