#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "SEA UCO";
const char* password = "SeaUco666";

// WebServer Instantiation
ESP8266WebServer server(80);

//Web Page Variable
String webPage = "";
String webPageLedOn = ""; 

const char MAIN_page[] PROGMEM = R"=====(
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Click to turn <a href="/ledOn">LED ON</a><br>
Click to turn <a href="/">LED OFF</a><br>
<hr>
</center>
</body>
</html>
)=====";

void ledOff(){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Led off");
  server.send(200, "text/html", MAIN_page);
}

void ledOn(){
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Led on");
  server.send(200, "text/html", MAIN_page);
}

void setup(void){
  
  delay(1000);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); 
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
  
  //Web Page handler on root "/" using .send() method from ESP8266WebServer class
  server.on("/", ledOff);
  server.on("/ledOn", ledOn);
  
  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
}
