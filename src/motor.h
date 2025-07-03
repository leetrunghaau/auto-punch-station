#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
public:
    Motor(uint8_t pin);
    void begin();
    void on();
    void off();
    bool isOn();

private:
    uint8_t _pin;
    bool _isOn;
};

#endif
