#ifndef PROCESS_H
#define PROCESS_H

#include "motor.h"
#include "heater.h"

// Defines the states of the machine
enum SystemState {
    IDLE,
    CONVEYOR_MOVING_IN,
    PUNCHING_DOWN,
    WAITING,
    PUNCHING_UP,
    CONVEYOR_MOVING_OUT
};

class Process
{
public:
    Process(Motor &motorPunch, Motor &motorConveyor, Heater &heater);
    void begin();
    void loop();

private:
    Motor &_motorPunch;
    Motor &_motorConveyor;
    Heater &_heater;

    SystemState _currentState;
    unsigned long _waitStartTime;

    void handleIdle();
    void handleConveyorIn();
    void handlePunchDown();
    void handleWaiting();
    void handlePunchUp();
    void handleConveyorOut();
};

#endif
