# Traffic Light with Night Mode and Button Control

## Description

This project implements a traffic light control system using Arduino, with LEDs simulating red, green, and yellow lights. The code allows you to switch between two modes:

1. **Normal Mode**: The traffic light automatically cycles through the red, green, and yellow states with predefined durations for each light.
2. **Night Mode**: The yellow light blinks every 500 ms, indicating that the system is in night mode.

A button is used to toggle between these modes, and button debounce is implemented to avoid false triggering. The system also includes Serial logs for monitoring and debugging.

## Features

* **Traffic Light Control** with LEDs representing the red, yellow, and green lights.
* **Night Mode** where the yellow LED blinks every 500 ms.
* **Button Control**: Switch between normal and night modes.
* **Button Debounce**: Ensures accurate button state readings.
* **Serial Logs** for debugging and monitoring system status.

## Components

* **Arduino** (Uno, Nano, or any compatible board).
* **3 LEDs** (red, yellow, and green).
* **1 Button** (to toggle between modes).
* **Pull-up Resistor** for the button (if needed).

## Wiring Diagram

* **Red LED**: Connected to pin 11 of the Arduino.
* **Yellow LED**: Connected to pin 5 of the Arduino.
* **Green LED**: Connected to pin 8 of the Arduino.
* **Button**: Connected to pin 2 of the Arduino (configured with internal pull-up).

## Code Structure

The code is divided into the following sections:

### 1. **Initial Setup**

* Initializes Serial communication.
* Configures the pins for LEDs and the button.
* Sets the initial states for the LEDs and runs a startup test.

### 2. **Main Loop**

* **Updates the button state**: Detects changes in button state and toggles between modes.
* **Night Mode**: If night mode is active, the yellow LED blinks every 500 ms.
* **Normal Mode**: Switches between the red, green, and yellow lights based on predefined timings.

### 3. **Control Functions**

* **`updateButtonState`**: Monitors the button state and handles debounce to avoid multiple triggers due to noise.
* **`updateTrafficLight`**: Controls the transitions between the red, green, and yellow lights in normal mode.
* **`blinkYellow`**: Controls the blinking of the yellow LED in night mode.
* **`allLedsOff`**: Turns off all LEDs.
* **`testLeds`**: Runs an LED test during startup.

## Example Serial Output

During execution, the system will send messages to the Serial Monitor, reporting on the system's status and transitions between modes. Examples:

```
System started. Night mode enabled.
Button pressed - starting debounce...
Night mode: OFF
Transition: RED → GREEN
Transition: GREEN → YELLOW
Transition: YELLOW → RED
...
```

## Notes

* The system starts in **night mode** when powered on.
* The duration of each light in normal mode is configurable and can be easily adjusted in the `TIME_RED`, `TIME_GREEN`, and `TIME_YELLOW` variables.
* Mode switching (normal ↔ night) is triggered by pressing the button, and debounce is implemented to prevent unwanted activations.

## How to Use

1. **Connect the components** as shown in the wiring diagram.
2. **Upload the code** to the Arduino using the Arduino IDE.
3. **Open the Serial Monitor** to track the system's status.
4. **Press the button** to toggle between normal and night modes.

## License

This code is provided under the [MIT License](https://opensource.org/licenses/MIT).
