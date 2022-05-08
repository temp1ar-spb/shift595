#include <shift595.h>

shift595::shift595(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin, const uint8_t chipCount) { // (data, clock, latch, chip amount)
    _clockPin =  clockPin;
    _dataPin  = dataPin;
    _latchPin =  latchPin;
    _chipCount =  chipCount;
}
bool shift595::get(const uint8_t pin) { return (_values >> (_chipCount * 8 - 1 - pin)) & 1;} // pin - from 0 to chipcount*8 -1
uint64_t shift595::getAll() {return _values;}
void shift595::set(const uint8_t pin, bool value) 
{
    (value) ? (_values |= (1ul << (_chipCount * 8 - 1 - pin))) : (_values &= ~(1ul << (_chipCount * 8 - 1 - pin))); //pin - from 0 to chipcount*8 -1
    update();
}
void shift595::setAll(uint64_t values) 
{
    _values = values;
    update();
}
void shift595::setAllLow() {
    uint64_t j = 1ul;
    for (int i = 0; i < (_chipCount * 8); i++){
        _values &= ~j;
        j <<= 1;
    }
    update();
}
void shift595::setAllHigh() {
    uint64_t j = 1ul;
    for (int i = 0; i < (_chipCount * 8); i++){
        _values |= j;
        j <<= 1;
    }
    update();
}
void shift595::update()
{
    writeP(_latchPin, 0);
    uint64_t j = 1ul;
    for (int i = 0; i < (_chipCount * 8); i++) {
        (j & _values) ? writeP(_dataPin, 1) : writeP(_dataPin, 0);
    j <<= 1;
    writeP(_clockPin, 1);
    writeP(_clockPin, 0);
  }  
  writeP(_latchPin, 1);
}

//fastest pin write structure for arduino. make sense for big amount of chips or chips matrix. 
//101us with classical arduino functions and only 8 with this one
void writeP(uint8_t pin, bool x) {  
  if (x == 1) {
    if (pin < 8) PORTD |= 1 << pin;
    else if (pin < 14) PORTB |= 1 << (pin - 8);
    else if (pin < 20) PORTC |= 1 << (pin - 14);
    else return;
  }
  else {
     if (pin < 8) PORTD &= ~(1 << pin);
    else if (pin < 14) PORTB &= ~(1 << (pin - 8));
    else if (pin < 20) PORTC &= ~(1 << (pin - 14));
    else return;
  }
  
}
