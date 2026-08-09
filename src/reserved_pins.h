#ifndef RESERVED_PINS_H
#define RESERVED_PINS_H

#include <Arduino.h>
#include <stddef.h>

class ReservedPinManager {
public:
    static ReservedPinManager& getInstance();

    void init();
    bool isReserved(int pin) const;
    bool isSafeForUser(int pin) const;
    bool isInputOnly(int pin) const;

private:
    static constexpr size_t MAX_TRACKED_PINS = 40;
    bool used_[MAX_TRACKED_PINS]{};

    ReservedPinManager() = default;
    ReservedPinManager(const ReservedPinManager&) = delete;
    ReservedPinManager& operator=(const ReservedPinManager&) = delete;
};

void initReservedPins();
bool validateHardwarePinout();

#endif
