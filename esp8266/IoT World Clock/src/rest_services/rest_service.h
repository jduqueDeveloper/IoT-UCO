#ifndef REST_SERVICE_H
#define REST_SERVICE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WString.h>
#include <ArduinoJson.h>
#include "mqtt_services/mqtt_service.h"

#define TIME_SERVER "http://worldtimeapi.org/api/timezone/"

//declare httpclient and wificlient objects (used by mqtt and rest services)
extern HTTPClient http;
extern WiFiClient client;

extern String get_date(String timezone);
String json_process_response(String json_response);
String get_day_name(char day_num);
String get_month_name(uint8 day_num);
String compose_date(
    char year[4],
    uint8 month,
    char day_of_month[2],
    char day_of_week,
    char hour[5]);

#endif // !REST_H
