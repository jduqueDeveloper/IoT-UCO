#ifndef MQTT_SERVICE
#define MQTT_SERVICE

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "credentials.h"
#include "rest_services/rest_service.h"

#define INPUT_TOPIC "input"
#define ALIVE_TOPIC "alive"
#define STATUS_REQ_TOPIC "StatusRequest"
#define OUTPUT_TOPIC "Output"
#define JSON_STATUS "JsonStatus"

extern bool new_message;
extern PubSubClient mqtt_client;
extern String message;

extern void reconnect();
extern void begin_mqtt();
extern void publish(const char* topic, String date);

#endif
