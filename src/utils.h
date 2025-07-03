#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

inline void waitForRelease(uint8_t pin)
{
    while (digitalRead(pin) == LOW)
    {
        delay(10);
    }
}

#endif
