#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "credentials.h"
#include "rest_services/rest_service.h"
#include "mqtt_services/mqtt_service.h"

//declare httpclient and wificlient objects (used by mqtt and rest services)
HTTPClient http;
WiFiClient client;

//declare  mqttclient object (used by mqtt service)
PubSubClient mqtt_client(client);

void setup()
{
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  begin_mqtt();
  delay(2000);
}

void loop()
{

  if (!mqtt_client.connected())
  {
    reconnect();
  }

  // mqttclient check for new connections
  mqtt_client.loop();

  
  //Handle new message
  if (new_message)
  {
    new_message = false;
    mqtt_client.disconnect();
    delay(1000);

    Serial.println("Trying to get hour");
    String date = get_date(message);

    if (!date.equals("Fail"))
    {
      Serial.println(date);
      publish(OUTPUT_TOPIC, date);
    }
  }
}