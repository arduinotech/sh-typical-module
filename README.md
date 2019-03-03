# Typical module for smart home on Arduino
This module can be installed in every room in your home. It allows you to control the light, and also transmits information about temperature and humidity.

To control the smart home should be used hub, such as a Smart Home, OpenHab or Domoticz. 

The module is a thin client. He himself does not make any decisions, all scripts are on the hub. The module only transmits data on movement, temperature and humidity, and also receives commands to turn on and off the light.

The module is connected via etnernet using a shield w5100 and uses the MQTT protocol to exchange information with hub.

This code is just an example. To use it, it must be finalized, and the hub of the smart home must be installed and configured.

![Arduino alarm clock schema](https://raw.githubusercontent.com/arduinotech/sh-typical-module/master/schema.png)

Used components:
* arduino uno: [1](http://ali.pub/348fnb) [2](http://ali.pub/34wrzq) [3](http://ali.pub/34ws2u)
* arduino ethernet shield w5100: [1](http://ali.pub/34yhi2) [2](http://ali.pub/35xz36) [3](http://ali.pub/35xz6v)
* relay (I use solid state omron): [1](http://ali.pub/36082o) [2](http://ali.pub/36083u) [3](http://ali.pub/360866)
* move sensor PIR HC-SR501: [1](http://ali.pub/3608h9) [2](http://ali.pub/3608im) [3](http://ali.pub/3608js)
* DHT22: [1](http://ali.pub/35y994) [2](http://ali.pub/35y9de) [3](http://ali.pub/35y9gp)
* speaker: [1](http://ali.pub/360940) [2](http://ali.pub/36095k) [3](http://ali.pub/360974)
