#include "sd_card.h"
#include <vector>
#include <algorithm>

SDCardModule sdCard;

bool SDCardModule::init() {
    sdSPI.begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, SD_CS);
    if (!SD.begin(SD_CS, sdSPI)) {
        lastError = "Card mount failed!";
        Serial.println("[SD] " + lastError);
        ready = false;
        return false;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        lastError = "No card attached!";
        Serial.println("[SD] " + lastError);
        ready = false;
        return false;
    }
    Serial.printf("[SD] Card ready. Size: %lluMB\n", SD.cardSize() / (1024 * 1024));
    ready = true;
    lastError = "";

    createDir(SD_LOG_DIR);
    createDir(SD_CAPTURE_DIR);
    createDir(SD_CONFIG_DIR);
    createDir(SD_PHISHING_DIR);
    createDir(SD_SCRIPTS_DIR);
    return true;
}

bool SDCardModule::isReady() { return ready; }

bool SDCardModule::writeFile(const char* path, const char* data) {
    if (!ready) return false;
    if (SD.exists(path)) SD.remove(path);
    File file = SD.open(path, FILE_WRITE);
    if (!file) return false;
    bool ok = file.print(data);
    file.close();
    return ok;
}

bool SDCardModule::appendFile(const char* path, const char* data) {
    if (!ready) return false;
    File file = SD.open(path, FILE_APPEND);
    if (!file) return false;
    bool ok = file.print(data);
    file.close();
    return ok;
}

String SDCardModule::readFile(const char* path, size_t maxSize) {
    if (!ready) return "";
    File file = SD.open(path);
    if (!file) return "";
    String content = "";
    content.reserve(maxSize < file.size() ? maxSize : file.size());
    size_t bytesRead = 0;
    while (file.available() && bytesRead < maxSize) {
        content += (char)file.read();
        bytesRead++;
    }
    file.close();
    return content;
}

bool SDCardModule::writeBinary(const char* path, uint8_t* data, size_t len) {
    if (!ready) return false;
    if (SD.exists(path)) SD.remove(path);
    File file = SD.open(path, FILE_WRITE);
    if (!file) return false;
    size_t written = file.write(data, len);
    file.close();
    return written == len;
}

bool SDCardModule::appendBinary(const char* path, uint8_t* data, size_t len) {
    if (!ready) return false;
    File file = SD.open(path, FILE_APPEND);
    if (!file) return false;
    size_t written = file.write(data, len);
    file.close();
    return written == len;
}

size_t SDCardModule::readBinary(const char* path, uint8_t* buffer, size_t maxSize) {
    if (!ready) return 0;
    File file = SD.open(path);
    if (!file) return 0;
    size_t bytesRead = file.read(buffer, maxSize);
    file.close();
    return bytesRead;
}

bool SDCardModule::deleteFile(const char* path) {
    if (!ready) return false;
    return SD.remove(path);
}

bool SDCardModule::renameFile(const char* oldPath, const char* newPath) {
    if (!ready) return false;
    if (!SD.exists(oldPath)) return false;
    if (SD.exists(newPath)) SD.remove(newPath);
    return SD.rename(oldPath, newPath);
}

bool SDCardModule::copyFile(const char* srcPath, const char* dstPath) {
    if (!ready) return false;
    File src = SD.open(srcPath);
    if (!src) return false;
    if (SD.exists(dstPath)) SD.remove(dstPath);
    File dst = SD.open(dstPath, FILE_WRITE);
    if (!dst) {
        src.close();
        return false;
    }
    uint8_t buf[512];
    size_t bytes;
    bool success = true;
    while ((bytes = src.read(buf, sizeof(buf))) > 0) {
        if (dst.write(buf, bytes) != bytes) {
            success = false;
            break;
        }
    }
    src.close();
    dst.close();
    if (!success && SD.exists(dstPath)) {
        SD.remove(dstPath);
    }
    return success;
}

bool SDCardModule::exists(const char* path) {
    if (!ready) return false;
    return SD.exists(path);
}

size_t SDCardModule::fileSize(const char* path) {
    if (!ready) return 0;
    File file = SD.open(path);
    if (!file) return 0;
    size_t sz = file.size();
    file.close();
    return sz;
}

String SDCardModule::readLine(File &file) {
    String line = "";
    while (file.available()) {
        char c = file.read();
        if (c == '\n') break;
        if (c != '\r') line += c;
    }
    return line;
}

String SDCardModule::getLogs(const char* path, int count, size_t maxLineLength) {
    if (!ready) return "SD not ready";
    File file = SD.open(path);
    if (!file) return "File not found";

    std::vector<size_t> linePositions;
    size_t pos = 0;
    bool hasNewline = false;
    while (file.available()) {
        char c = file.read();
        if (c == '\n') {
            linePositions.push_back(pos);
            pos = file.position();
            hasNewline = true;
        }
    }
    if (!hasNewline && pos > 0) {
        linePositions.push_back(pos);
    }
    file.close();

    int start = max(0, (int)linePositions.size() - count);
    String result = "";
    result.reserve(count * maxLineLength);

    file = SD.open(path);
    if (!file) return "Error reopening file";

    for (int i = start; i < (int)linePositions.size(); i++) {
        size_t targetPos = linePositions[i];
        file.seek(targetPos);
        String line = readLine(file);
        if (line.length() > maxLineLength) {
            line = line.substring(0, maxLineLength) + "...";
        }
        result += line + "\n";
    }
    file.close();
    return result;
}

void SDCardModule::listDir(const char* dirname, uint8_t levels, String &output) {
    if (!ready) return;
    File root = SD.open(dirname);
    if (!root || !root.isDirectory()) return;
    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            output += "[DIR] " + String(file.name()) + "\n";
            if (levels) listDir(file.path(), levels - 1, output);
        } else {
            output += String(file.name()) + " (" + String(file.size()) + "B)\n";
        }
        file = root.openNextFile();
    }
}

bool SDCardModule::createDir(const char* path) {
    if (!ready) return false;
    if (SD.exists(path)) return true;
    return SD.mkdir(path);
}

bool SDCardModule::removeDir(const char* path) {
    if (!ready) return false;
    if (!SD.exists(path)) return true;
    return SD.rmdir(path);
}

uint64_t SDCardModule::totalBytes() { return ready ? SD.totalBytes() : 0; }
uint64_t SDCardModule::usedBytes() { return ready ? SD.usedBytes() : 0; }
uint64_t SDCardModule::freeBytes() { return ready ? (SD.totalBytes() - SD.usedBytes()) : 0; }