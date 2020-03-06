#include "mqtt_service.h"

const char* mqttServer = "192.168.1.16";
const int mqttPort = 1883;

String location = "";
bool new_location = false;

enum topics
{
    input,
    alive,
    StatusRequest,
    JsonStatus,
    Output
};

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    location = "";
    for (unsigned int i = 0; i < length; i++)
    {
        location += (char)payload[i];
    }
    Serial.println(location);
    new_location = true;
}

void setup_mqtt(){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void reconnect()
{
    while (!client.connected() || (client.state() < 0))
    {
        Serial.println("Trying to connect with broker");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str()))
        {
            Serial.println("Connected");
            client.subscribe(INPUT_TOPIC);
        }
        delay(1000);
    }
    publish(ALIVE_TOPIC, "I'm alive");
}

void publish(const char *topic, String date)
{
     if (client.state() < 0)
    {
        reconnect();
    }
    delay(500);
    char message[50];
    date.toCharArray(message, 50);
    client.publish(topic, message);
    Serial.println("published");
}