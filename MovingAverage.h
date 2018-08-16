#pragma once

class MovingAverage {
  public:
    MovingAverage();
    MovingAverage( int32_t initValue );
    void fill( int32_t value );
		void append( int32_t value );
		float get();
		bool isComplete();    
  private:
    static const uint8_t RING_BUFFER_SIZE = 64;
    uint8_t _index = 0;
    int32_t _ringBuffer[RING_BUFFER_SIZE];
    bool _isComplete = false;
    float _average;
    void recalculate();
};


