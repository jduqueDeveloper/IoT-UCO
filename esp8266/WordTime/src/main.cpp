#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "rest.h"

const char* ssid = "****";
const char* password =  "****";
const char* mqttServer = "****";
const int mqttPort = 	0;
const char* mqttUser = "****";
const char* mqttPassword = "****";
const char* TopicSub = "worldTime";
const char* TopicPub = "worldTime";

WiFiClient espClient;
PubSubClient client(espClient);

/********* Setup wifi ***************************
   setup wifi connect to wifi with the constants
   defined up
   while does not connect print a "."
   if connect then print the local ip
************************************************/
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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

/********* MQTT Callback ***************************
   here is defined the logic to execute after
   a messages arrives in the desired
   topic, for this example the variable:
   TopicSub
************************************************/
void callback(char* topic, byte* payload, unsigned int length) {
String payloadString;
  //Notify about message arrived 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  //Print the message received
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    payloadString += (char)payload[i];
  }

  restRequest(payloadString);
  //Prints with visualization purposes
  Serial.println();
  Serial.println("-----------------------");
 
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
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  
  //Publish to desired topic and subscribe for messages
  client.publish(TopicPub, "bitches every where");
  client.subscribe(TopicSub);
 
}

extern void publishMQTT(String message){

char buf[502]; 
message.toCharArray(buf, 502);
Serial.println(buf);
client.publish(TopicPub,buf);

}
 
void loop() {
  //MQTT client loop
  client.loop();
}
