#ifndef PROCESS_H
#define PROCESS_H

#include "motor.h"
#include "heater.h"
#include "utils.h" // Include for Button class

// Defines the states of the machine
enum SystemState {
    IDLE,
    CONVEYOR_MOVING_IN,
    PUNCHING_DOWN,
    WAITING,
    PUNCHING_UP,
    CONVEYOR_MOVING_OUT,
    ERROR_STATE // Added for timeout handling
};

class Process
{
public:
    Process(Motor &motorPunch, Motor &motorConveyor, Heater &heater,
            Button &startButton, Button &punchLimitUp, Button &punchLimitDown,
            Button &conveyorLimitIn, Button &conveyorLimitOut);
    void begin();
    void loop();

private:
    Motor &_motorPunch;
    Motor &_motorConveyor;
    Heater &_heater;

    // Button and Limit Switch references
    Button &_startButton;
    Button &_punchLimitUp;
    Button &_punchLimitDown;
    Button &_conveyorLimitIn;
    Button &_conveyorLimitOut;

    SystemState _currentState;
    unsigned long _waitStartTime;
    unsigned long _motorTimeoutStartTime; // For motor timeout

    void handleIdle();
    void handleConveyorIn();
    void handlePunchDown();
    void handleWaiting();
    void handlePunchUp();
    void handleConveyorOut();
    void handleError(); // New error handler
};

#endif
