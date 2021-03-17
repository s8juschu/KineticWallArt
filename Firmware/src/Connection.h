#ifndef CONNECTION_H
#define CONNECTION_H

#include <MQTT.h>
#include <ESP8266WiFi.h>
#include "LED.h"

class ConnectionClass {
    public:
        void setup();
        void loop();
        void send(String topic, String payload);
};

extern ConnectionClass Connection;

#endif