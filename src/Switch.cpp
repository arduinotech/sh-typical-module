#include <Arduino.h>
#include "Switch.h"

Switch::Switch(int pin)
{
    _pin = pin;
}

void Switch::init()
{
    pinMode(_pin, OUTPUT);
}

void Switch::turnOn()
{
    digitalWrite(_pin, HIGH);
}

void Switch::turnOff()
{
    digitalWrite(_pin, LOW);
}
