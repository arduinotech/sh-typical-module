#include <Arduino.h>
#include "MotionSensor.h"

MotionSensor::MotionSensor(int pin)
{
    _pin = pin;
}

void MotionSensor::init()
{
    pinMode(_pin, INPUT);
}

bool MotionSensor::isMotion()
{
    return (digitalRead(_pin) == HIGH);
}
