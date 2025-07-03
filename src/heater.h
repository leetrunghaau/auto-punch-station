#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>

class Heater
{
public:
    Heater(uint8_t pinControl);
    void begin();
    void turnOn();
    void turnOff();
    bool isOn();

private:
    uint8_t _pinControl;
    bool _state;
};

#endif
