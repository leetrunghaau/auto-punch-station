#include <Arduino.h>

#include "motor.h"
#include "process.h"
#include "heater.h"
#include "pinConfig.h"

// Initialize motors with their respective H-Bridge control pins
Motor motorPunch(PIN_MOTOR_PUNCH);
Motor motorConveyor(PIN_MOTOR_CONVEYOR);
Heater heater(PIN_HEATER);

// The process controller orchestrates everything
Process process(motorPunch, motorConveyor, heater);

void setup()
{
  // Initialize all components
  motorPunch.begin();
  motorConveyor.begin();
  heater.begin();
  process.begin();
}

void loop()
{
  // The main loop continuously runs the process state machine
  process.loop();
}
