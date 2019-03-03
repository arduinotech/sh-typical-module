#ifndef MotionSensor_h
#define MotionSensor_h

#include <Arduino.h>

class MotionSensor
{
    public:
        MotionSensor(int pin);
        void init();
        bool isMotion();
    private:
        int _pin;
};

#endif
