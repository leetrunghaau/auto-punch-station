#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

class Button {
public:
    Button(uint8_t pin, unsigned long debounceDelay = 50);
    bool isPressed();
    bool wasPressed(); // Detects a single press event

private:
    uint8_t _pin;
    unsigned long _debounceDelay;
    int _lastButtonState;  // the previous reading from the input pin
    unsigned long _lastDebounceTime; // the last time the output pin was toggled
    bool _currentButtonState; // the current debounced state
    bool _lastReportedState; // the last state reported by wasPressed
};

#endif