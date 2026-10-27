
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address: commonly 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Analog input
const int batteryPin = A0;

// LED pins: low to high indication
const int ledPins[] = {2, 3, 4, 5, 6};
const int ledCount = 5;

// Voltage divider resistors
const float R1 = 1000.0;
const float R2 = 1000.0;

// ADC reference settings
const float referenceVoltage = 5.0;
const float adcMaximum = 1023.0;

// Example thresholds for a nominal 9 V battery.
// These are illustrative, not a universal battery
// state-of-charge calibration.
const float thresholds[] = {
  6.0, 6.8, 7.4, 8.0, 8.5
};

float readBatteryVoltage() {
  long total = 0;

  // Average several readings to reduce noise
  for (int i = 0; i < 10; i++) {
    total += analogRead(batteryPin);
    delay(5);
  }

  float adcValue = total / 10.0;
  float voltageAtA0 =
      adcValue * referenceVoltage / adcMaximum;

  return voltageAtA0 * (R1 + R2) / R2;
}

void updateLEDs(float voltage) {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(
      ledPins[i],
      voltage >= thresholds[i] ? HIGH : LOW
    );
  }
}

void setup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Battery Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();
}

void loop() {
  float voltage = readBatteryVoltage();

  updateLEDs(voltage);

  lcd.setCursor(0, 0);
  lcd.print("Battery: ");
  lcd.print(voltage, 2);
  lcd.print(" V  ");

  lcd.setCursor(0, 1);

  if (voltage < thresholds[0]) {
    lcd.print("VERY LOW        ");
  } else if (voltage < thresholds[1]) {
    lcd.print("LOW             ");
  } else if (voltage < thresholds[2]) {
    lcd.print("MEDIUM          ");
  } else if (voltage < thresholds[3]) {
    lcd.print("GOOD            ");
  } else if (voltage < thresholds[4]) {
    lcd.print("HIGH            ");
  } else {
    lcd.print("LEVEL HIGH      ");
  }

  delay(500);
}
