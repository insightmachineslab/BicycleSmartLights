#pragma once

class MotionDetector {
  public:
    MotionDetector( uint8_t pin );
    uint8_t getPin();
    bool motionDetected();
    void onInterrupt();
  private:
    const uint16_t MAX_INTERRUPT_INTERVAL = 5000;   // [ms]
    uint8_t _pin; 
    uint32_t _lastInterruptMillis = 0;    
};


