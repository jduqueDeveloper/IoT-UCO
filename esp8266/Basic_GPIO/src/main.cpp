#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Replace with your network credentials
const char* ssid = "xxxxxx";
const char* password = "xxxxxxxx";
int led1 = D1;

 
void setup(void){

  //Serial Communication and WiFi Connection kick off
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led1, INPUT_PULLUP); 
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop(void){

  //Turn on/off Built in Led with 1s delay
  if(digitalRead(led1) == HIGH){
  digitalWrite(LED_BUILTIN, HIGH);
  }else{ 
  digitalWrite(LED_BUILTIN, LOW);
  }

}
