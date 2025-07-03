# Schematic Documentation

## Machine Punch Controller Schematic Overview

This schematic implements a **multi-channel AC control system** based on ATmega328P, capable of:

- Driving up to **8 AC loads** (motors, heaters, lamps)
- Reading up to **8 opto-isolated digital inputs**
- Zero-crossing detection for AC phase control
- Providing status LEDs for each channel
- Isolated logic via optocouplers

---

## 🔹 1. Power Supply

### HLK-10M05
- **Purpose:** Convert AC 220V to DC 5V
- **Outputs:**
  - +5V DC (VCC_2)
  - GND

**Filtering capacitors:**
- C3, C4, C12

**Usage:**
- Power for MCU, optocouplers, logic circuits

---

## 🔹 2. MCU Section

### ATmega328P
- **Role:** Central controller
- **Features:**
  - 32 digital IOs
  - UART serial communication
  - SPI ISP programming interface
  - Clock: 16 MHz crystal (Y1) + C7/C11 capacitors
  - Reset circuitry: Pull-up resistor + capacitor
- **Power:** +5V from HLK-10M05

**Important Pins:**
- Digital outputs to EL357 for AC control
- Digital inputs from EL357 for sensor feedback
- SPI pins for programming

---

## 🔹 3. Output Control (AC Loads)

**Each AC load channel consists of:**
- EL357 optocoupler
  - **Input:** MCU output pin
  - **Output:** Triggers MOC3063M LED
- MOC3063M (Opto-Triac driver with zero-cross detection)
  - **Input:** From EL357
  - **Output:** Drives external Triac (not shown)
- Status LED to indicate output ON

**Total Channels: 8**

| Channel No. | EL357 Ref | MOC3063M Ref | MCU Control Pin |
|---|---|---|---|
| 1 | *4 | U1 | D4 |
| 2 | *5 | U2 | D3 |
| 3 | *6 | U4 | D2 |
| 4 | *7 | U5 | A5 |
| 5 | *8 | - | A4 |
| 6 | *9 | - | A3 |
| 7 | *10 | - | A1 |
| 8 | *11 | - | A2 |

**Notes:**
- MOC3063M zero-cross pin is connected (some channels)
- Each EL357 output is in series with a resistor and LED
- Output loads are connected to AC mains via Triac

---

## 🔹 4. Input Control (Sensors / Limit Switches)

**Each input signal:**
- Comes through an EL357 optocoupler
  - Isolates external circuits from MCU
- Pulled up to VCC via resistor

**Total Inputs: 8**

| Input Ref | Signal Name | MCU Pin |
|---|---|---|
| A_O | Input A | D3 |
| B_O | Input B | D4 |
| C_O | Input C | A5 |
| D_O | Input D | A1 |
| E_O | Input E | A3 |
| F_O | Input F | A4 |
| G_O | Input G | A2 |
| H_O | Input H | (Optional) |

**Example uses:**
- Limit switch Punch Down
- Limit switch Punch Up
- Conveyor Start
- Conveyor End
- Start button
- Emergency stop

---

## 🔹 5. Zero-Cross Detection Circuits

**Purpose:**
- Detect AC zero-cross events
- Allow phase-controlled firing of Triac (future PWM control)

**Components:**
- 4x MOC3063M wired for zero-cross detection
- Outputs can be fed into MCU interrupt pins

**Refs:**
- U1, U2, U4, U5

---

## 🔹 6. Status LEDs

**Each output channel has:**
- LED (0805) in series with 2k resistor
- Lights up when channel is active

**Purpose:**
- Visual confirmation of outputs ON/OFF

---

## 🔹 7. Communication & Programming

**Serial Communication:**
- TXD, RXD pins exposed
- Used for monitoring and debugging

**ISP Interface:**
- SPI pins (MISO, MOSI, SCK)
- Supports firmware upload via programmer

---

## 🔹 8. Suggested Output Mapping

| Function | EL357 Channel | MCU Pin | Notes |
|---|---|---|---|
| Heater | *4 | D4 | Output AC load 1 |
| Motor Punch | *5 | D3 | Output AC load 2 |
| Motor Conveyor | *6 | D2 | Output AC load 3 |
| Indicator Lamp | *7 | A5 | Output AC load 4 |
| (Free) | *8 | A4 | Spare channel |
| (Free) | *9 | A3 | Spare channel |
| (Free) | *10 | A1 | Spare channel |
| (Free) | *11 | A2 | Spare channel |

---

## 🔹 9. Optional Extensions

- Connect Zero-Cross outputs to MCU for phase control
- Use unused channels for additional motors or heaters
- Add EEPROM for configuration
- Integrate OLED display

---

## ⚠ Safety Notes

- All AC wiring must be done with proper insulation
- Optocoupler isolation protects MCU but not relay wiring
- Ensure proper grounding of chassis
- Use fuses and circuit breakers for overload protection

---

## 📝 References

- `schematic.pdf` schematic diagram
- MOC3063M datasheet
- EL357 datasheet

