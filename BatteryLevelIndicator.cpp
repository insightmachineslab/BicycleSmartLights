#include <Arduino.h>
#include "BatteryLevelIndicator.h"

BatteryLevelIndicator::BatteryLevelIndicator( uint8_t batteryVoltagePin, uint8_t greenLedPin, uint8_t redLedPin )
  : _batteryVoltagePin(batteryVoltagePin), _greenLedPin(greenLedPin), _redLedPin(redLedPin) {
	pinMode(_batteryVoltagePin, INPUT);
	pinMode(_redLedPin, OUTPUT);
  pinMode(_greenLedPin, OUTPUT);
  digitalWrite(_redLedPin, HIGH);   // High is off
  digitalWrite(_greenLedPin, HIGH); // High is off
}

void BatteryLevelIndicator::update() {
  uint32_t t1 = millis();
  if ( (t1-_lastBlinkMillis) > BLINK_INTERVAL ) {
    int val = analogRead(_batteryVoltagePin); 
    bool batteryLevelWarningOn = val < BATTERY_WARNING_LEVEL;
    digitalWrite(_redLedPin, batteryLevelWarningOn ? LOW : HIGH);
    digitalWrite(_greenLedPin, batteryLevelWarningOn ? HIGH: LOW);
    delay(10);
    digitalWrite(_redLedPin, HIGH);
    digitalWrite(_greenLedPin, HIGH);  
    _lastBlinkMillis = t1;
  }
}

