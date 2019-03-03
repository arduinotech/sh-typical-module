#ifndef Switch_h
#define Switch_h

#include <Arduino.h>

class Switch
{
    public:
        Switch(int pin);
        void init();
        void turnOn();
        void turnOff();
    private:
        int _pin;
};

#endif
