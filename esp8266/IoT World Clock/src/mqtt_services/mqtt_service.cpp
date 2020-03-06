#include "mqtt_service.h"

bool new_message = false;
String message = "";

enum topics
{
    alive,
    StatusRequest,
    JsonStatus,
    Output
};

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    message = "";
    for (unsigned int i = 0; i < length; i++)
    {
        //Serial.print((char)payload[i]);
        message += (char)payload[i];
    }
    Serial.println(message);
    new_message = true;
}

void reconnect()
{
    while (!mqtt_client.connected() || (mqtt_client.state() < 0))
    {
        Serial.println("Trying to connect with broker");

        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        // Attempt to connect
        if (mqtt_client.connect(clientId.c_str()))
        {
            Serial.println("Connected");
            mqtt_client.subscribe(INPUT_TOPIC);
        }
        delay(1000);
    }
    publish(ALIVE_TOPIC, "I'm alive");
}

void begin_mqtt()
{
    mqtt_client.setServer(MQTT_BROKER_URL, MQTT_BROKER_PORT);
    mqtt_client.setCallback(callback);
}

void publish(const char *topic, String date)
{

    if (mqtt_client.state() < 0)
    {
        reconnect();
    }

    delay(500);
    char message[50];
    date.toCharArray(message, 50);
    mqtt_client.publish(topic, message);
    Serial.println("published");
}
