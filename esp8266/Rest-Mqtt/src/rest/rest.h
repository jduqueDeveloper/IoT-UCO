#ifndef REST_H
#define REST_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <WString.h>
#include <ArduinoJson.h>
#include <mqtt/mqtt_service.h>


extern HTTPClient http;
extern WiFiClient clientHttp;
extern String HTTPQuery(String url);
extern String JsonConvert(String JsonDoc);
String dayName(char day_num);
String monthName(uint8 day_num);
#endif