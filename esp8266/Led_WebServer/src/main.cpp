#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "SATURNO";
const char* password = "87654321";

// WebServer Instantiation
ESP8266WebServer server(80);

const char* www_username = "admin";
const char* www_password = "1234";

#define LED D1

const char MAIN_page[] PROGMEM = R"=====(
<html>
<body>
<center>
<h1></h1><br>
<a href="/ledMode"><img height="500" width="500" src="https://www.elektor.com/media/catalog/product/cache/2b4bee73c90e4689bbc4ca8391937af9/1/6/169034-91f-web.jpg" /></a>
<a href="/ledProtoboard"><img height="540" width="480" src="https://pngimage.net/wp-content/uploads/2018/06/red-led-png-6.png" /></a>
</center>
</body>
</html>
)=====";


void ledMode(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.send(200, "text/html", MAIN_page);
}

void ledProtoboard(){
  digitalWrite(LED, !digitalRead(LED));
  server.send(200, "text/html", MAIN_page);
}

void setup(void){
  
  delay(1000);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(LED, OUTPUT);
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
  server.on("/ledMode", ledMode);
  server.on("/ledProtoboard", ledProtoboard);

  server.on("/", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    server.send(200, "text/html", MAIN_page);
  });
  
  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
}
