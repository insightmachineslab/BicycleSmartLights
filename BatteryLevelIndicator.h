#pragma once

class BatteryLevelIndicator {
  public:
    BatteryLevelIndicator( uint8_t batteryVoltagePin, uint8_t greenLedPin, uint8_t redLedPin );
    void update();
  private:
    const uint16_t BATTERY_WARNING_LEVEL = 520; // Reference voltage is 3.3V. The VCC pin on Arduino Pro Mini will output 3.3V as long as the RAW voltage is greater than 3.3V. When it is below, VCC will be the same as RAW. We want to know when RAW is equal to VCC.
    const uint32_t BLINK_INTERVAL = 3000; // [ms]
    uint8_t _batteryVoltagePin;
    uint8_t _greenLedPin;
    uint8_t _redLedPin;
    uint32_t _lastBlinkMillis = 0;    
};


