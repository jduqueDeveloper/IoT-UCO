#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "xxx";
const char* password =  "xxx";
const char* mqttServer = "ip_broker";
const int mqttPort = 1883;
const char* TopicSub = "test";
const char* TopicPub = "test";

String url = "http://worldtimeapi.org/api/timezone/";

HTTPClient http;
WiFiClient clientHttp;

WiFiClient mqttClient;
PubSubClient client(mqttClient);


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

/********* MQTT Callback ***************************
   here is defined the logic to execute after
   a messages arrives in the desired
   topic, for this example the variable:
   TopicSub
************************************************/

String HTTPQuery(String url){

  String query = "";

    if (http.begin(clientHttp, url))
     {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();
 
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            query = http.getString();
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

  return query;
}

void callback(char* topic, byte* payload, unsigned int length) {

  //Notify about message arrived 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  String timePetition = "";
  String urlTopic = url;
  for (int i = 0; i < length; i++) {
    timePetition += (char)payload[i];
    urlTopic += (char)payload[i];
  }
  
  
  //Prints with visualization purposes
  Serial.println("Data time in json format of " + timePetition + " area: ");  

  String jsonQuery = HTTPQuery(urlTopic);
  Serial.println(jsonQuery);
}


void setup() {
 
  //Start Serial Communication
  Serial.begin(115200);
  
  //Connect to WiFi
  setup_wifi();

  //Connect to MQTT Broker
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  //MQTT Connection Validation
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  
  //Publish to desired topic and subscribe for messages
  client.publish(TopicPub, "America/Bogota");
  client.subscribe(TopicSub);
 
}
 
void loop() {
  
  //MQTT client loop
  client.loop();
}
