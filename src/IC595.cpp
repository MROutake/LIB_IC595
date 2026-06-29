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
    digitalWrite(_dataPin, LOW);

    // Ausgänge deaktiviert (Hi-Z) lassen, bis ein definierter Zustand anliegt.
    // Verhindert zufälliges Anziehen der Relais beim Power-On.
    digitalWrite(_enablePin, HIGH);      // OE inaktiv (HIGH)

    // Schieberegister leeren (MR aktiv LOW), danach wieder freigeben.
    digitalWrite(_masterResetPin, LOW);
    delayMicroseconds(5);
    digitalWrite(_masterResetPin, HIGH);

    // Genullten Schieberegister-Inhalt ins Ausgangsregister latchen.
    digitalWrite(_storageClkPin, HIGH);
    digitalWrite(_storageClkPin, LOW);

    // Jetzt liegt ein definierter 0-Zustand an → Ausgänge aktivieren.
    digitalWrite(_enablePin, LOW);       // OE aktiv (LOW)

    return true;
}

bool IC595::setData(uint32_t bitmask, uint8_t length, int delay_ms)
{
    // length = Anzahl Bytes (1–4), passend zur RJ45-Bitmask. 1 Byte = 1 595-Chip.
    if (length == 0 || length > 4) return false;

    digitalWrite(_storageClkPin, LOW);

    // MSB zuerst → von höchstem Byte runter
    for (int i = length - 1; i >= 0; i--) {
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