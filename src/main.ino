/**
 * Typical module for smart home. Created on arduino uno with ethernet shield and sensors,
 * it send data to home assistant by mqtt protocol. Also contains a relay and switches the
 * light on or off on the incoming command.
 * 
 * The circuit:
 * - arduino uno
 * - ethernet shield W5100
 * - move sensor PIR HC-SR501
 * - speaker
 * - relay
 * - temperature and humidity sensor DHT22
 * 
 * By https://arduino.tech
 * 
 */
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "Switch.h"
#include "SensorDHT22.h"
#include "MotionSensor.h"
#include "Mqtt.h"

// global settings
#define LOOP_MILLIS 1000
#define SERIAL_PORT_SPEED 115200
#define ARDUINO_UNIQ_ID "arduinoRoom1Client"

// Home Assistant device ids
#define SWITCH_LIGHT "room1_light"
#define SENSOR_MOTION "room1_motion"
#define SENSOR_TEMPERATURE "root1_temperature"
#define SENSOR_HUMIDITY "room1_humidity"


// DHT22
const int dht22Pin = 5;
// Motion sensor
const int motionPin = 6;
// Switcher
const int switchLightPin = 7;
// Speaker
const int speakerPin = 2;

// network settings
byte serverIP[] = {192, 168, 1, 10};
byte localIP[] = {192, 168, 1, 145};
byte mac[] = {0xDE, 0xED, 0xBA, 0xEF, 0xEF, 0xBB};
const int mqttPort = 1883;

// creation sensors and other classes
Switch switchLight(switchLightPin);
SensorDHT22 dht22Sensor(dht22Pin);
MotionSensor motionSensor(motionPin);
Mqtt mqttFormatter;

// network
EthernetClient ethClient;
PubSubClient client(ethClient);

void callback(char* topic, byte* payload, unsigned int length)
{
  String strPayload;

  char channelBuffer[200];
  String channel;
  String command;

  for (unsigned int i = 0; i < length; i++) {
    strPayload += (char)(payload[i]);
  }

  String topicName;
  topicName = topic;
  String subscribeLight = mqttFormatter.getTopicCommand(SWITCH_LIGHT);

  if (topicName == subscribeLight) {
    if (strPayload == "0") {
      switchLight.turnOff();

      channel = mqttFormatter.getTopicState(SWITCH_LIGHT);
      channel.toCharArray(channelBuffer, (channel.length() + 1));
      client.publish(channelBuffer, SWITCH_OFF);
    } else {
      switchLight.turnOn();

      channel = mqttFormatter.getTopicState(SWITCH_LIGHT);
      channel.toCharArray(channelBuffer, (channel.length() + 1));
      client.publish(channelBuffer, SWITCH_ON);
    }
  }
}

void reconnect()
{
  char subscribeBuffer[50];
  while (!client.connected()) {
    if (client.connect(ARDUINO_UNIQ_ID)) {
      String subscribeLight = mqttFormatter.getTopicCommand(SWITCH_LIGHT);
      subscribeLight.toCharArray(subscribeBuffer, subscribeLight.length() + 1);
      client.subscribe(subscribeBuffer);
    } else {
      delay(5000);
    }
  }
}

void setup()
{
  tone(speakerPin, 1000);

  dht22Sensor.init();
  motionSensor.init();

  switchLight.init();
  switchLight.turnOn();
  delay(1500);
  switchLight.turnOff();

  client.setServer(serverIP, mqttPort);
  client.setCallback(callback);
  Ethernet.begin(mac, localIP);

  delay(1500);
  noTone(speakerPin);
}

void loop()
{
  static bool allSwitchesOffSended = false;
  static unsigned long lastLoop = 0;

  char channelBuffer[200];
  char commandBuffer[200];
  String channel;
  String command;

  unsigned long now = millis();
  if (lastLoop > now) lastLoop = 0;

  // Save current values
  static float saveDht22Temp = 0.0;
  static float saveDht22Hum = 0.0;
  static bool isMotion = false;
  static unsigned long lastMotionDetected = 0;


  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (allSwitchesOffSended == false) {
    channel = mqttFormatter.getTopicState(SWITCH_LIGHT);
    channel.toCharArray(channelBuffer, (channel.length() + 1));
    client.publish(channelBuffer, SWITCH_OFF);
    allSwitchesOffSended = true;
  }

  if (now > (lastLoop + LOOP_MILLIS)) {
    float t = dht22Sensor.getTemp();
    if (!isnan(t)) {
      if (t != saveDht22Temp) {
        channel = mqttFormatter.getTopicState(SENSOR_TEMPERATURE);
        channel.toCharArray(channelBuffer, (channel.length() + 1));
        command = (int)t;
        command.toCharArray(commandBuffer, (command.length() + 1));
        client.publish(channelBuffer, commandBuffer);
        saveDht22Temp = t;
      }
    }

    float h = dht22Sensor.getHumi();
    if (!isnan(h)) {
      if (h != saveDht22Hum) {
        channel = mqttFormatter.getTopicState(SENSOR_HUMIDITY);
        channel.toCharArray(channelBuffer, (channel.length() + 1));
        command = (int)h;
        command.toCharArray(commandBuffer, (command.length() + 1));
        client.publish(channelBuffer, commandBuffer);
        saveDht22Hum = h;
      }
    }

    bool newMotion = motionSensor.isMotion();
    if (newMotion) {
      lastMotionDetected = now;
    }
    if ((newMotion != isMotion) && (newMotion || (((now - lastMotionDetected) / 1000) > 11))) {
      channel = mqttFormatter.getTopicState(SENSOR_MOTION);
      channel.toCharArray(channelBuffer, (channel.length() + 1));
      client.publish(channelBuffer, newMotion ? SWITCH_ON : SWITCH_OFF);
      isMotion = newMotion;
    }

    lastLoop = now;
  }
}
