#include "utils.h"

Button::Button(uint8_t pin, unsigned long debounceDelay)
    : _pin(pin), _debounceDelay(debounceDelay),
      _lastButtonState(HIGH), _lastDebounceTime(0),
      _currentButtonState(HIGH), _lastReportedState(HIGH)
{
    pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
    int reading = digitalRead(_pin);

    if (reading != _lastButtonState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _currentButtonState) {
            _currentButtonState = reading;
        }
    }

    _lastButtonState = reading;
    return (_currentButtonState == LOW); // Assuming active LOW button
}

bool Button::wasPressed()
{
    bool pressed = isPressed();
    if (pressed && !_lastReportedState) {
        _lastReportedState = true;
        return true;
    } else if (!pressed) {
        _lastReportedState = false;
    }
    return false;
}
