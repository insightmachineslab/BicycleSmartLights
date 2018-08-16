#include "LedController.h"
#include "MovingAverage.h"
#include "RpmMeter.h"
#include "MotionDetector.h"
#include "BatteryLevelIndicator.h"
#include "LowPower.h"

const uint8_t MOTION_DETECTOR_PIN = PD3;
const uint8_t REED_SWITCH_PIN = PD2;
const uint8_t LIGHT_SENSOR_PIN = A0;
const uint8_t FRONT_LED_PIN = PD5;
const uint8_t REAR_LED_PIN = PD6;
const uint8_t AUTO_MODE_PIN = A3;
const uint8_t BATTERY_INDICATOR_RED_PIN = 10;
const uint8_t BATTERY_INDICATOR_GREEN_PIN = 11;
const uint8_t BATTERY_VOLTAGE_PIN = A1;

const float THRESHOLD_LIGHT_LEVEL = 5.0;
const uint8_t LOOP_DELAY = 40;  // [ms]

LedController frontLedController( FRONT_LED_PIN );
LedController rearLedController( REAR_LED_PIN );
MovingAverage averageLightLevel;
RpmMeter rpmMeter(REED_SWITCH_PIN);
MotionDetector motionDetector(MOTION_DETECTOR_PIN);
BatteryLevelIndicator batteryLevelIndicator(BATTERY_VOLTAGE_PIN, BATTERY_INDICATOR_GREEN_PIN, BATTERY_INDICATOR_RED_PIN);

void setup() {
  pinMode(AUTO_MODE_PIN, INPUT_PULLUP);  
  attachInterrupt( digitalPinToInterrupt(REED_SWITCH_PIN), onReedSwitchPinFalling, FALLING);
  attachInterrupt( digitalPinToInterrupt(MOTION_DETECTOR_PIN), onMotionDetectorPinChange, CHANGE);  
  delay(10);
  if ( !inAutoMode() ) {  // "On" mode
    frontLedController.setReferenceBrightness(0.75);
    frontLedController.setMode(LedControllerMode::On);
    rearLedController.setReferenceBrightness(0.5);
    rearLedController.setMode(LedControllerMode::Blinking);
  }
}

void loop() {
  uint32_t t0 = millis();
  if ( inAutoMode() ) {
    updateLightsInAutoMode();
  } else {
    updateLightsInOnMode();
  }
  batteryLevelIndicator.update();
  uint32_t dt = min( LOOP_DELAY, millis() - t0 );
  delay( LOOP_DELAY-dt );
}

bool inAutoMode() {
  return digitalRead(AUTO_MODE_PIN) == LOW;
}

void updateLightsInAutoMode() {
  updateLightLevel();
  
  bool isDark = true; //averageLightLevel.get() < THRESHOLD_LIGHT_LEVEL;
  
  uint8_t rpm = rpmMeter.getRpm();
  bool motionDetected = motionDetector.motionDetected();
  bool powerDown = false;

  if ( isDark ) {
    if ( rpm > 0 ) {
      frontLedController.setMode(LedControllerMode::On);
      rearLedController.setMode(LedControllerMode::Blinking);
    } else if ( motionDetected ) {
      frontLedController.setMode(LedControllerMode::Blinking);
      rearLedController.setMode(LedControllerMode::Blinking);
    } else {
      frontLedController.setMode(LedControllerMode::Off);
      rearLedController.setMode(LedControllerMode::Off);
      powerDown = true;
    }
  } else {
    frontLedController.setMode(LedControllerMode::Off);
    rearLedController.setMode(LedControllerMode::Off);
    powerDown = true;
  }

  frontLedController.update();
  rearLedController.update();

  if ( powerDown && frontLedController.isDark() && rearLedController.isDark() ) {
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  }
}

void updateLightsInOnMode() {
  frontLedController.update();
  rearLedController.update();
}

void updateLightLevel() {
  int val = analogRead(LIGHT_SENSOR_PIN);
  if ( averageLightLevel.isComplete() ) {
    averageLightLevel.append(val);
  } else {
    averageLightLevel.fill(val);
  }
}

void onReedSwitchPinFalling() {
  rpmMeter.onInterrupt();
}

void onMotionDetectorPinChange() {
  motionDetector.onInterrupt();  
}

