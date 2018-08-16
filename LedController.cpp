#include <Arduino.h>
#include "LedController.h"

LedController::LedController( uint8_t pin ) 
  : _pin(pin), _currentBrightness(0.0), _referenceBrightness(1.0), _mode(LedControllerMode::Off) {
  pinMode(_pin, OUTPUT);  
  updatePWM();
}

void LedController::update() {
  
  switch (_mode) {
    case LedControllerMode::Blinking:
        _currentBrightness -= BRIGHTNESS_DELTA;
        if (_currentBrightness < -1.5) {  // The negative value adds a short break between impulses
          _currentBrightness = 1.0;
        }
        break;
    case LedControllerMode::On:
        if ( _currentBrightness < 1.0 ) {
          _currentBrightness = min(1.0, _currentBrightness+BRIGHTNESS_DELTA);
        }
        break;
    default:  // Off
        if ( _currentBrightness > 0.0 ) {
          _currentBrightness = max(0.0, _currentBrightness-BRIGHTNESS_DELTA);
        }
    }  

  updatePWM();
}

void LedController::setMode( LedControllerMode mode ) {
  _mode = mode;
}

LedControllerMode LedController::getMode() {
  return _mode;
}

void LedController::setReferenceBrightness( float referenceBrightness ) {
  _referenceBrightness = referenceBrightness;
}

float LedController::getReferenceBrightness() {
  return _referenceBrightness;
}

float LedController::getCurrentBrightness() {
  return _currentBrightness;
}

bool LedController::isDark() {
  return _currentBrightness <= 0.0;
}

void LedController::updatePWM() {
  int pwmValue = max(0, round(MAX_PWM_VALUE*_currentBrightness*_referenceBrightness));
  analogWrite(_pin, pwmValue);  
}

