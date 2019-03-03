#ifndef SensorDHT22_h
#define SensorDHT22_h

#include <Arduino.h>
#include <DHT.h>

class SensorDHT22
{
    public:
        SensorDHT22(int pin);
        void init();
        float getTemp();
        float getHumi();
    private:
        int _pin;
        DHT* _dht;
};

#endif
