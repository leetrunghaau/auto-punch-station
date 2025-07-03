#ifndef PINCONFIG_H
#define PINCONFIG_H

// Outputs based on schematic.md (AC loads via Triac)
#define PIN_HEATER 4            // MCU D4 -> EL357 -> MOC3063M -> Triac
#define PIN_MOTOR_PUNCH 3       // MCU D3 -> EL357 -> MOC3063M -> Triac
#define PIN_MOTOR_CONVEYOR 2    // MCU D2 -> EL357 -> MOC3063M -> Triac
#define PIN_INDICATOR_LAMP A5   // MCU A5 -> EL357 -> MOC3063M -> Triac

// Inputs based on schematic.md (Opto-isolated)
// Note: The schematic has generic inputs A-H. We map them logically.
#define PIN_START_BUTTON A1         // Input D
#define PIN_PUNCH_LIMIT_UP A2       // Input G
#define PIN_PUNCH_LIMIT_DOWN A3     // Input E
#define PIN_CONVEYOR_LIMIT_IN A4    // Input F
#define PIN_CONVEYOR_LIMIT_OUT A5   // Input C - NOTE: A5 is used for both output and input in the schematic, which is a conflict. Remapping to A0 for safety.
#define PIN_CONVEYOR_LIMIT_OUT_SAFE A0 // Using A0 as a safe alternative to avoid conflict on A5.

#endif
