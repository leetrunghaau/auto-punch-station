#include "motor.h"

Motor::Motor(uint8_t pin)
    : _pin(pin), _isOn(false) {}

void Motor::begin()
{
    pinMode(_pin, OUTPUT);
    off(); // Ensure motor is off initially
}

void Motor::on()
{
    digitalWrite(_pin, HIGH); // Activate the optocoupler/triac
    _isOn = true;
}

void Motor::off()
{
    digitalWrite(_pin, LOW); // Deactivate the optocoupler/triac
    _isOn = false;
}

bool Motor::isOn()
{
    return _isOn;
}
