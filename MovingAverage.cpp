#include <Arduino.h>
#include "MovingAverage.h"

MovingAverage::MovingAverage() : MovingAverage::MovingAverage(0) {}

MovingAverage::MovingAverage( int32_t initValue ) {
  for ( uint8_t i=0; i<RING_BUFFER_SIZE; i++ ) {
  	_ringBuffer[i] = initValue;
  }
}

void MovingAverage::fill( int32_t value ) {
  for ( uint8_t i=0; i<RING_BUFFER_SIZE; i++ ) {
    _ringBuffer[i] = value;
  }
  _isComplete = true;
}

void MovingAverage::append( int32_t value ) {
	_ringBuffer[_index] = value;
	recalculate();
	_index++;
	if ( _index == RING_BUFFER_SIZE ) {
		_index = 0;
		_isComplete = true;
	}
}

float MovingAverage::get() {
	return _average;
}

bool MovingAverage::isComplete() {
	return _isComplete;
}

void MovingAverage::recalculate() {
	_average = 0.0;
	for ( uint8_t i=0; i<RING_BUFFER_SIZE; i++ ) {
  	_average += _ringBuffer[i];
  }
  _average /= RING_BUFFER_SIZE;
}
