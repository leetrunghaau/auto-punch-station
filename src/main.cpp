#include <Arduino.h>

#include "motor.h"
#include "process.h"
#include "heater.h"
#include "pinConfig.h"
#include "utils.h"

// Initialize motors with their respective H-Bridge control pins
Motor motorPunch(PIN_PUNCH_MOTOR_A, PIN_PUNCH_MOTOR_B);
Motor motorConveyor(PIN_CONVEYOR_MOTOR_A, PIN_CONVEYOR_MOTOR_B);
Heater heater(PIN_HEATER);

// Initialize buttons and limit switches
Button startButton(PIN_START_BUTTON);
Button punchLimitUp(PIN_PUNCH_LIMIT_UP);
Button punchLimitDown(PIN_PUNCH_LIMIT_DOWN);
Button conveyorLimitIn(PIN_CONVEYOR_LIMIT_IN);
Button conveyorLimitOut(PIN_CONVEYOR_LIMIT_OUT);

// The process controller orchestrates everything
Process process(motorPunch, motorConveyor, heater, startButton, punchLimitUp, punchLimitDown, conveyorLimitIn, conveyorLimitOut);

void setup()
{
  // Initialize all components
  motorPunch.begin();
  motorConveyor.begin();
  heater.begin();
  // No need to call begin() on buttons, as pinMode is set in constructor
  process.begin();
}

void loop()
{
  // The main loop continuously runs the process state machine
  process.loop();
}
