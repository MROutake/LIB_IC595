#include "IC595.h"

IC595::IC595() {}

bool IC595::begin(int shiftClkPin, int storageClkPin, int enablePin, int dataPin, int masterResetPin)
{
    _shiftClkPin = shiftClkPin;
    _storageClkPin = storageClkPin;
    _enablePin = enablePin;
    _dataPin = dataPin;
    _masterResetPin = masterResetPin;

    pinMode(_shiftClkPin, OUTPUT);
    pinMode(_storageClkPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    pinMode(_masterResetPin, OUTPUT);

    digitalWrite(_shiftClkPin, LOW);
    digitalWrite(_storageClkPin, LOW);
    digitalWrite(_enablePin, LOW);      // OE aktiv (LOW)
    digitalWrite(_dataPin, LOW);

    digitalWrite(_masterResetPin, HIGH); // wichtig!

    return true;
}

bool IC595::setData(uint32_t bitmask, uint8_t length, int delay_ms)
{
    if (length > 32) return false;

    digitalWrite(_storageClkPin, LOW);

    // Anzahl Bytes berechnen
    uint8_t bytes = (length + 7) / 8;

    // MSB zuerst → von höchstem Byte runter
    for (int i = bytes - 1; i >= 0; i--) {
        uint8_t dataByte = (bitmask >> (i * 8)) & 0xFF;
        shiftOut(_dataPin, _shiftClkPin, MSBFIRST, dataByte);
        delay(delay_ms);
    }

    // Latch auslösen
    digitalWrite(_storageClkPin, HIGH);
    delay(delay_ms);
    digitalWrite(_storageClkPin, LOW);

    return true;
}
``