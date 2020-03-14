#include <ESP8266HTTPClient.h>
#include "rest.h"
#include "main.h"

//HTTP Server URL
String url = "http://worldtimeapi.org/api/timezone/";
String payload  = "";

String restRequest(String request)
{
   HTTPClient http;
 url += request;
 
   if (http.begin(url)) //Start connection
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();  // GET Request
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            payload = http.getString();   // Get HTTP response
            Serial.println(payload);   // Print content of payload
      
            publishMQTT(payload);
            

            //client.setServer(mqttServer, mqttPort);
            //client.publish(TopicPub,"hola pirobo");
            //parseJson(payload);

         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
 
      http.end();
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }
 
   delay(15000);
}