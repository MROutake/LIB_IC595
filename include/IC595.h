#pragma once

#include <Arduino.h>

class IC595 {
public:
    IC595();

    bool begin(int shiftClkPin, int storageClkPin, int enablePin, int dataPin, int masterResetPin);

    /**
     * @brief Bitmask in die Schieberegister schreiben und latchen.
     *
     * @param bitmask  Auszugebender Wert. Bit N → Ausgang Q_N.
     * @param length   Anzahl Bytes (1–4). 1 Byte = 8 Ausgänge = 1 595-Chip.
     *                 Gleiche Einheit wie die RJ45-Bitmask (Little-Endian).
     * @param delay_ms Verzögerung je Byte/Latch (0 = keine).
     * @return false bei ungültiger length (0 oder > 4).
     */
    bool setData(uint32_t bitmask, uint8_t length, int delay_ms);

private:
    int _shiftClkPin;
    int _storageClkPin;
    int _enablePin;
    int _dataPin;
    int _masterResetPin;
};