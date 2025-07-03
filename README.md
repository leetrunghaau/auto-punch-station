# Automated Conveyor, Punch, and Heat Station

## Project Overview

This is an embedded systems project developed with PlatformIO to control a small automated workstation.  
The system manages a conveyor belt, a punching mechanism, and a heating element to perform a **sequential manufacturing process**.

The target hardware is an ATmega328-based microcontroller, commonly found on boards like the Arduino Uno or Nano.

## Core Components

The system controls the following hardware:

1. **Heater (`heater`)**
   - The heating element is **always ON** throughout the machine operation.
2. **Conveyor Motor (`motorConveyor`)**
   - Moves products along the conveyor belt.
3. **Punch Motor (`motorPunch`)**
   - Activates the punching or pressing mechanism.
4. **Limit Switches**
   - Four limit switches detect positions of the punch and conveyor:
     - Conveyor IN position
     - Conveyor OUT position
     - Punch DOWN position
     - Punch UP position
5. **Start Button**
   - A push-button to start the complete cycle.
## Workflow

The operational sequence, implemented in the `Process` class, is as follows:

1. The system remains idle until the **Start Button** is pressed.
2. **Heater turns ON and remains ON.**
3. The **Conveyor Motor** runs forward until the **IN limit switch** is triggered (product moves into position).
4. The **Punch Motor** moves **DOWN** until the **DOWN limit switch** is triggered.
5. The system **waits until the heater reaches sufficient temperature** (or a fixed heating delay).
6. The **Punch Motor** moves partially **UP** (dở lên) until the **UP limit switch** is triggered.
7. The **Conveyor Motor** runs again to move the product OUT until the **OUT limit switch** is triggered.
8. The system returns to idle, waiting for the next cycle.
9. **Heater remains ON** for subsequent cycles.

This logic ensures the heater is always active and the punch/conveyor operate in precise sequence.

---

## Software & Structure

- **Framework:** [Arduino](https://www.arduino.cc/)
- **Build System:** [PlatformIO](https://platformio.org/)
- **Language:** C++
- **Key Files:**
  - `src/main.cpp`: Entry point. Initializes all objects and starts the main loop.
  - `src/process.cpp`: Contains the core workflow logic described above.
  - `src/motor.cpp`: Motor control class (start/stop).
  - `src/heater.cpp`: Heater control class (on/off).
  - `src/pinConfig.h`: Defines pin mapping for all hardware.

---
## How to Build

1.  Install [Visual Studio Code](https://code.visualstudio.com/) and the [PlatformIO IDE extension](https://platformio.org/platformio-ide).
2.  Clone this repository.
3.  Open the project folder in VS Code.
4.  To build the project, run the command: `platformio run`
5.  To build and upload to a connected board, run: `platformio run --target upload`

## Known Issues

-   The `main.cpp` file is currently out of sync with the `Process` class. It fails to create and pass the required `Heater` object during the initialization of the `process` object, which will cause a **compilation error**. This needs to be fixed for the project to build successfully.
