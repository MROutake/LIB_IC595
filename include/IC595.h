#pragma once

# include <Arduino.h>

class IC595 {


public: 
    IC595();

    bool begin(int SHIFT_CLK_PIN, int STORAGE_CLK_PIN,int ENABLE_PIN, int DATA_PIN);
    bool setData( uint32_t bitmask, uint8_t length);
    


private:


    int _SHIFT_CLK_PIN;
    int _STORAGE_CLK_PIN;
    int _ENABLE_PIN;
    int _DATA_PIN;
    int _MASTER_RESET_PIN;


