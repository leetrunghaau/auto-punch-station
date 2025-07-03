#include "heater.h"

Heater::Heater(uint8_t pinControl)
    : _pinControl(pinControl), _state(false) {}

void Heater::begin()
{
    pinMode(_pinControl, OUTPUT);
    digitalWrite(_pinControl, LOW);
}

void Heater::turnOn()
{
    digitalWrite(_pinControl, HIGH);
    _state = true;
}

void Heater::turnOff()
{
    digitalWrite(_pinControl, LOW);
    _state = false;
}

bool Heater::isOn()
{
    return _state;
}
