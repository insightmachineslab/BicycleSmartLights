#pragma once

enum class LedControllerMode { Off, On, Blinking };  

class LedController {
  public:
    LedController( uint8_t pin );
    void setMode( LedControllerMode mode );
    LedControllerMode getMode();
    void setReferenceBrightness( float referenceBrightness );
    float getReferenceBrightness();    
    float getCurrentBrightness();    
    void update();
    bool isDark();
  private:
    const uint8_t MAX_PWM_VALUE = 255;
    const float BRIGHTNESS_DELTA = 0.12;
    uint8_t _pin;
    float _referenceBrightness;
    float _currentBrightness;
    LedControllerMode _mode;
    void updatePWM();

};


