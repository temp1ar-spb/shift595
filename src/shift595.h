#pragma once
#include <Arduino.h>

class shift595 
{
public:
    shift595(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin, const uint8_t chipCount);
    
    void setAll(uint64_t values);
    void update();
    void set(const uint8_t pin, bool value);
    void getAll();
    void get (uint8_t pin);
    void setAllLow();
    void setAllHigh(); 
 
private:
    uint8_t _clockPin;
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _chipCount;
    uint64_t _values;
};
