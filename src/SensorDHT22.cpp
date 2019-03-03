#include <Arduino.h>
#include "SensorDHT22.h"

SensorDHT22::SensorDHT22(int pin)
{
    _pin = pin;
}

void SensorDHT22::init()
{
    _dht = new DHT(_pin, DHT22);
    _dht->begin();
}

float SensorDHT22::getTemp()
{
    return _dht->readTemperature();
}

float SensorDHT22::getHumi()
{
    return _dht->readHumidity();
}
