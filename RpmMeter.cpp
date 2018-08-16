#include <Arduino.h>
#include "RpmMeter.h"


RpmMeter::RpmMeter( uint8_t pin ) : _pin(pin) {
	pinMode(_pin, INPUT_PULLUP);
}

uint8_t RpmMeter::getPin() {
	return _pin;
} 

uint8_t RpmMeter::getRpm() {
	uint32_t dt = millis() - _lastInterruptMillis;
  if ( dt > MAX_INTERRUPT_INTERVAL ) {
    _rpm = 0;
    _lastInterruptMillis = 0;
  }
	return _rpm;
}

void RpmMeter::onInterrupt() {
	uint32_t t1 = millis();
  if ( _lastInterruptMillis == 0 ) {
    _lastInterruptMillis = t1;    
    _rpm = 1;
    return;
  }

  uint32_t dt = t1-_lastInterruptMillis;
  if ( dt > MAX_INTERRUPT_INTERVAL ) {
    _rpm = 0;
    _lastInterruptMillis = 0;
  } else if ( dt > MIN_INTERRUPT_INTERVAL ) {
    _rpm = MILLIS_PER_MINUTE/dt;
    _lastInterruptMillis = t1;    
  } else {
  	// Any signal that comes before MIN_INTERRUPT_INTERVAL is treated as noise and ignored
  }
}

