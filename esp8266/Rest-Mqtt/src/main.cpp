#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <rest/rest.h>
#include <mqtt/mqtt_service.h>
 
const char* ssid = "xxx";
const char* password =  "xxx";
const char* mqttServer = "192.168.0.107";
const int mqttPort = 1883;

HTTPClient http;
WiFiClient clientHttp;

WiFiClient mqttCli;
PubSubClient client(mqttCli);

/********* Setup wifi ***************************
   setup wifi connect to wifi with the constants
   defined up
   while does not connect print a "."
   if connect then print the local ip
************************************************/
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println("");
  Serial.println("WiFi connected");
}


void setup() {
 
  //Start Serial Communication
  Serial.begin(115200);
  delay(10);

  //Connect to WiFi
  setup_wifi();

  //Connect to MQTT Broker
  mqtt_init();
 
  //MQTT Connection Validation
  mqtt_conect();
  
  //Subscribe for messages
  //client.subscribe(InputTopic);
 
}
 
void loop() {
  
  if (!client.connected())
  {
  mqtt_conect();
  }

  //MQTT client loop
  client.loop();

  if (message_arrived)
  {
    message_arrived = false;
    client.disconnect();
    delay(1000);

    Serial.println("Trying to get hour");
    String jsonQuery = HTTPQuery(urlTopic);
    //String JsonConverted = JsonConvert(jsonQuery);

    //String dataFormat = JsonConvert(jsonQuery);
    //publishDataFormat(dataFormat);
    if (!jsonQuery.equals("Fail"))
    {
      Serial.println(jsonQuery);
      publishDataFormat(jsonQuery);
    }
  }

}
