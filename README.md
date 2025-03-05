# chainbuddy
arduino based dispenser to spray the bike chain with cleaner or lubricant as and when required using Arduino microcontroller.

An Arduino project that uses a servo motor to automatically press a spray can nozzle at timed intervals or on demand.

## Features

- **Dual Operation Modes**:
  - Manual mode: Control via button or potentiometer
  - Auto mode: Automatic spraying at regular intervals

- **Customizable Parameters**:
  - Servo rest position (default: 0°)
  - Spray position (default: 45°)
  - Spray duration (default: 1 second)
  - Interval between sprays (default: 5 seconds)

## Hardware Requirements

- Arduino board (Uno, Nano, etc.)
- Standard servo motor (9-12kg/cm torque recommended)
- Push button (optional)
- Potentiometer (optional)
- Toggle/slide switch for mode selection (optional)
- Jumper wires
- Breadboard (for prototyping)

## Wiring Diagram

| Component | Arduino Pin |
|-----------|-------------|
| Servo Signal | D9 |
| Button | D2 |
| Potentiometer | A0 |
| Mode Switch | D3 |

## Installation

1. Connect the hardware as described in the wiring diagram
2. Download the `spray_can_controller.ino` file
3. Open with Arduino IDE
4. Upload to your Arduino board

## Usage

- **Manual Mode** (mode switch open/HIGH):
  - Press and hold the button to activate the spray
  - Use the potentiometer to fine-tune servo position
  
- **Auto Mode** (mode switch closed/LOW):
  - The servo will automatically press at intervals defined in the code
  - Edit the `sprayInterval` and `sprayDuration` values to customize

## Customization

You can easily modify these parameters in the code:

```cpp
const int restPosition = 0;      // Servo angle when not spraying
const int sprayPosition = 45;    // Servo angle when spraying
const int sprayDuration = 1000;  // How long to spray (milliseconds)
const int sprayInterval = 5000;  // Time between sprays (milliseconds)
