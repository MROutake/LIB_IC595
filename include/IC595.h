#pragma once

#include <Arduino.h>

class IC595 {
public:
    IC595();

    bool begin(int shiftClkPin, int storageClkPin, int enablePin, int dataPin, int masterResetPin);
    bool setData(uint32_t bitmask, uint8_t length, int delay_ms);

private:
    int _shiftClkPin;
    int _storageClkPin;
    int _enablePin;
    int _dataPin;
    int _masterResetPin;
};