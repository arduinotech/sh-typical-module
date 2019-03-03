#ifndef Mqtt_h
#define Mqtt_h

#include <Arduino.h>

#define SWITCH_ON "1"
#define SWITCH_OFF "0"
#define SWITCH_TOGGLE "Toggle"
#define MQTT_STATE "state"
#define MQTT_COMMAND "command"
#define TOPIC_DELIMER "/"

class Mqtt
{
    public:
        Mqtt();
        String getTopicCommand(const char *device);
        String getTopicState(const char *device);
};

#endif
