#include <Arduino.h>
#include "MotionDetector.h"


MotionDetector::MotionDetector( uint8_t pin ) : _pin(pin) {
	pinMode(_pin, INPUT_PULLUP);
}

uint8_t MotionDetector::getPin() {
	return _pin;
} 

bool MotionDetector::motionDetected() {
  uint32_t dt = millis() - _lastInterruptMillis;
  return _lastInterruptMillis > 0 && dt < MAX_INTERRUPT_INTERVAL;
}

void MotionDetector::onInterrupt() {
  _lastInterruptMillis = millis();
}
