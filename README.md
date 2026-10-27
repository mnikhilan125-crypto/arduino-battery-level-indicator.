# arduino-battery-level-indicatorArduino Battery Level Indicator

An Arduino-based project that measures battery voltage using a voltage divider and displays the calculated voltage on a 16×2 LCD with I²C communication.

Components

- Arduino Uno
- 16×2 LCD with I²C module
- Two 1 kΩ resistors
- Battery and breadboard
- Connecting wires

Working Principle

The voltage divider reduces the battery voltage to a level suitable for the Arduino's analog input (A0). The Arduino reads the voltage using its ADC, calculates the battery voltage, and displays the result on the LCD.

Technologies

- Arduino C++
- Analog-to-Digital Conversion (ADC)
- I²C communication

Repository Contents

- "BatteryLevelIndicator.ino" — Arduino source code
- "images/" — Circuit diagram and project photographs

Safety

Never connect a 9 V battery directly to the Arduino's 5 V pin or analog input. Verify the circuit and voltage-divider connections before powering the project.
