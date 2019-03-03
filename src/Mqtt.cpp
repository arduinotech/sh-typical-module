#include <Arduino.h>
#include "Mqtt.h"

Mqtt::Mqtt()
{
}

String Mqtt::getTopicCommand(const char *device)
{
    String topicName = MQTT_COMMAND;
    topicName += TOPIC_DELIMER;
    topicName += device;
    return topicName;
}

String Mqtt::getTopicState(const char *device)
{
    String topicName = MQTT_STATE;
    topicName += TOPIC_DELIMER;
    topicName += device;
    return topicName;
}
