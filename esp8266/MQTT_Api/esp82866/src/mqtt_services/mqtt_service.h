#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

extern bool new_location;
extern PubSubClient client;
extern String location;

#define INPUT_TOPIC "input"
#define ALIVE_TOPIC "alive"
#define STATUS_REQ_TOPIC "statusrequest"
#define JSON_STATUS "jsonstatus"
#define OUTPUT_TOPIC "output"

extern void reconnect();
extern void setup_mqtt();
extern void publish(const char* topic, String date);

#endif