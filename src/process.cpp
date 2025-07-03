#include "process.h"
#include "pinConfig.h"

Process::Process(Motor &motorPunch, Motor &motorConveyor, Heater &heater)
    : _motorPunch(motorPunch), _motorConveyor(motorConveyor), _heater(heater),
      _currentState(IDLE), _waitStartTime(0) {}

void Process::begin()
{
    pinMode(PIN_PUNCH_LIMIT_UP, INPUT_PULLUP);
    pinMode(PIN_PUNCH_LIMIT_DOWN, INPUT_PULLUP);
    pinMode(PIN_CONVEYOR_LIMIT_IN, INPUT_PULLUP);
    pinMode(PIN_CONVEYOR_LIMIT_OUT_SAFE, INPUT_PULLUP); // Using the safe pin
    pinMode(PIN_START_BUTTON, INPUT_PULLUP);

    // Always keep the heater on (as per new requirement)
    _heater.turnOn();
}

void Process::loop()
{
    // The core of the state machine
    switch (_currentState)
    {
    case IDLE:
        handleIdle();
        break;
    case CONVEYOR_MOVING_IN:
        handleConveyorIn();
        break;
    case PUNCHING_DOWN:
        handlePunchDown();
        break;
    case WAITING:
        handleWaiting();
        break;
    case PUNCHING_UP:
        handlePunchUp();
        break;
    case CONVEYOR_MOVING_OUT:
        handleConveyorOut();
        break;
    }
}

void Process::handleIdle()
{
    // Wait for the start button to be pressed
    if (digitalRead(PIN_START_BUTTON) == LOW)
    {
        // Debounce delay
        delay(50);
        if (digitalRead(PIN_START_BUTTON) == LOW)
        {
            _currentState = CONVEYOR_MOVING_IN;
        }
    }
}

void Process::handleConveyorIn()
{
    _motorConveyor.on();
    if (digitalRead(PIN_CONVEYOR_LIMIT_IN) == LOW)
    {
        _motorConveyor.off();
        _currentState = PUNCHING_DOWN;
    }
}

void Process::handlePunchDown()
{
    _motorPunch.on(); // Assuming 'on' moves it down
    if (digitalRead(PIN_PUNCH_LIMIT_DOWN) == LOW)
    {
        _motorPunch.off();
        _waitStartTime = millis();
        _currentState = WAITING;
    }
}

void Process::handleWaiting()
{
    if (millis() - _waitStartTime >= 3000)
    {
        _currentState = PUNCHING_UP;
    }
}

void Process::handlePunchUp()
{
    _motorPunch.on(); // Assuming 'on' moves it up (this might need hardware adjustment if it's a single direction motor)
    if (digitalRead(PIN_PUNCH_LIMIT_UP) == LOW)
    {
        _motorPunch.off();
        _currentState = CONVEYOR_MOVING_OUT;
    }
}

void Process::handleConveyorOut()
{
    _motorConveyor.on();
    if (digitalRead(PIN_CONVEYOR_LIMIT_OUT_SAFE) == LOW) // Using the safe pin
    { 
        _motorConveyor.off();
        _currentState = IDLE; // Cycle complete
    }
}
