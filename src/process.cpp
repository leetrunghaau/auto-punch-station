#include "process.h"
#include "pinConfig.h"

Process::Process(Motor &motorPunch, Motor &motorConveyor, Heater &heater,
                 Button &startButton, Button &punchLimitUp, Button &punchLimitDown,
                 Button &conveyorLimitIn, Button &conveyorLimitOut)
    : _motorPunch(motorPunch), _motorConveyor(motorConveyor), _heater(heater),
      _startButton(startButton), _punchLimitUp(punchLimitUp), _punchLimitDown(punchLimitDown),
      _conveyorLimitIn(conveyorLimitIn), _conveyorLimitOut(conveyorLimitOut),
      _currentState(IDLE), _waitStartTime(0), _motorTimeoutStartTime(0) {}

void Process::begin()
{
    // pinMode for input pins is handled by Button class constructor

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
    case ERROR_STATE:
        handleError();
        break;
    }
}

void Process::handleIdle()
{
    // Wait for the start button to be pressed
    if (_startButton.wasPressed())
    {
        _currentState = CONVEYOR_MOVING_IN;
        _motorTimeoutStartTime = millis(); // Start timeout for motor
    }
}

void Process::handleConveyorIn()
{
    _motorConveyor.forward();
    if (_conveyorLimitIn.isPressed())
    {
        _motorConveyor.stop();
        _currentState = PUNCHING_DOWN;
        _motorTimeoutStartTime = millis(); // Start timeout for motor
    } else if (millis() - _motorTimeoutStartTime >= MOTOR_TIMEOUT_MS) {
        _motorConveyor.stop();
        _currentState = ERROR_STATE;
    }
}

void Process::handlePunchDown()
{
    _motorPunch.forward(); // Move punch down
    if (_punchLimitDown.isPressed())
    {
        _motorPunch.stop();
        _waitStartTime = millis();
        _currentState = WAITING;
    } else if (millis() - _motorTimeoutStartTime >= MOTOR_TIMEOUT_MS) {
        _motorPunch.stop();
        _currentState = ERROR_STATE;
    }
}

void Process::handleWaiting()
{
    if (millis() - _waitStartTime >= HEATER_WAIT_TIME_MS)
    {
        _currentState = PUNCHING_UP;
        _motorTimeoutStartTime = millis(); // Start timeout for motor
    }
}

void Process::handlePunchUp()
{
    _motorPunch.reverse(); // Move punch up
    if (_punchLimitUp.isPressed())
    {
        _motorPunch.stop();
        _currentState = CONVEYOR_MOVING_OUT;
        _motorTimeoutStartTime = millis(); // Start timeout for motor
    } else if (millis() - _motorTimeoutStartTime >= MOTOR_TIMEOUT_MS) {
        _motorPunch.stop();
        _currentState = ERROR_STATE;
    }
}

void Process::handleConveyorOut()
{
    _motorConveyor.forward();
    if (_conveyorLimitOut.isPressed())
    { 
        _motorConveyor.stop();
        _currentState = IDLE; // Cycle complete
    } else if (millis() - _motorTimeoutStartTime >= MOTOR_TIMEOUT_MS) {
        _motorConveyor.stop();
        _currentState = ERROR_STATE;
    }
}

void Process::handleError()
{
    // Stop all motors
    _motorPunch.stop();
    _motorConveyor.stop();
    // Optionally, turn off heater or flash an error LED
    // _heater.turnOff(); 
    // Add code to indicate error (e.g., flash an LED)
    // For now, just stay in error state until reset
}