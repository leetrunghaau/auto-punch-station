#ifndef PINCONFIG_H
#define PINCONFIG_H

// Output Pins (based on schematic.md - Motor 1/2, Heater)
#define PIN_PUNCH_MOTOR_A 5    // Motor 1 - Forward
#define PIN_PUNCH_MOTOR_B 7    // Motor 1 - Reverse
#define PIN_CONVEYOR_MOTOR_A 6 // Motor 2 - Forward
#define PIN_CONVEYOR_MOTOR_B 8 // Motor 2 - Reverse
#define PIN_HEATER 4           // Heater

// Inputs based on schematic.md (Opto-isolated)
// Note: The schematic has generic inputs A-H. We map them logically.
#define PIN_START_BUTTON A1         // Input D
#define PIN_PUNCH_LIMIT_UP A2       // Input G
#define PIN_PUNCH_LIMIT_DOWN A3     // Input E
#define PIN_CONVEYOR_LIMIT_IN A4    // Input F
#define PIN_CONVEYOR_LIMIT_OUT A0 // Input C - Remapped from A5 to A0 to avoid conflict with PIN_INDICATOR_LAMP.

// Configuration values
#define HEATER_WAIT_TIME_MS 3000UL // Time to wait for heater to reach temperature
#define MOTOR_TIMEOUT_MS 10000UL   // Max time for a motor to reach its limit switch (10 seconds)

#endif
