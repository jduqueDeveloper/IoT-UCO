#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "mqtt_services/mqtt_service.h"
 
const char* ssid = "xxxxx";
const char* password =  "xxxx";
String urlServer = "http://192.168.1.16:8080/getHourByCountryWithCloudServer/";

WiFiClient espClient;
HTTPClient http;

PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print(F("Connecting to ")) ;
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String ServerRequest(String location)
{
   WiFiClient client;
   String url = urlServer + location;
   String date = "";
   if (http.begin(client, url)) //Iniciar conexión
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();  // Realizar petición
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
              date = http.getString();   // Obtener respuesta    
              publish(STATUS_REQ_TOPIC, "Ok request");   
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
   return date;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  setup_wifi();
  setup_mqtt();
  delay(2000);
}
 
void loop() {
   if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  if (new_location)
  {
    new_location = false;
    client.disconnect();
    delay(1000);
    Serial.println("Trying to get hour");
    String date = ServerRequest(location);
    if (!date.equals("Fail"))
    {
      Serial.println(date);
      publish(OUTPUT_TOPIC, date);
    }
  }
}