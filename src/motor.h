#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
public:
    Motor(uint8_t pinA, uint8_t pinB);
    void begin();
    void forward();
    void reverse();
    void stop();

private:
    uint8_t _pinA;
    uint8_t _pinB;
};

#endif