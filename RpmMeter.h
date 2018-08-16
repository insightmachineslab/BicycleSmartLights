#pragma once

class RpmMeter {
  public:
    RpmMeter( uint8_t pin );
    uint8_t getPin();
    uint8_t getRpm();
    void onInterrupt();
  private:
    const uint16_t MIN_INTERRUPT_INTERVAL = 100;   // [ms]
		const uint16_t MAX_INTERRUPT_INTERVAL = 2000;  // [ms]
		const uint16_t MILLIS_PER_MINUTE = 60*1000;    // [ms]
		uint8_t _pin; 
		uint8_t _rpm = 0; 
    uint32_t _lastInterruptMillis = 0;    
};








