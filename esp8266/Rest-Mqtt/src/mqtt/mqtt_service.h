#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include "rest/rest.h"

#define InputTopic "input"
#define AliveTopic "alive"
#define StatusRequestTopic "StatusRequest"
#define OutputTopic "Output"
#define JsonStatusTopic "JsonStatus"

#define url_api "http://worldtimeapi.org/api/timezone/"

extern const char* mqttServer;
extern const int mqttPort;
extern bool message_arrived;
extern String urlTopic;
extern PubSubClient client;

extern void mqtt_init();
extern void mqtt_conect();
extern void publishInTopic(const char* topic, const char* message);
extern void publishDataFormat(String message);



#endif