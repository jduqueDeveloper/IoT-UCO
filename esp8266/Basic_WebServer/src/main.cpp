#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "TP-LINK_3C02";
const char* password = "camila1234";
// WebServer Instantiation
ESP8266WebServer server(80);

//Web Page Variable

const char Server_Page[] PROGMEM = R"=====(
<html>
<body>
<center>
<h1></h1><br>
<style>
  .button{
    color: white
    padding: 20px 34px;
    text-aling: center;
    font-size: 20px;
    margin: 4px 2px;
    cursor: pointer;
  }

  .slider {
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 100%; /* Full-width */
  height: 25px; /* Specified height */
  background: #d3d3d3; /* Grey background */
  outline: none; /* Remove outline */
  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
  -webkit-transition: .2s; /* 0.2 seconds transition on hover */
  transition: opacity .2s;
}

</style>

<form>
  <button type = "submit" formaction = "/gpio1-on">Click me to do magic!</button>
  <button type = "submit" formaction = "/gpio1-off">Click me to finish the magic!</button>
</form>

<div class="slidecontainer">
  <input type="range" min="1" max="100" value="50" class="slider" id="myRange">
</div>

</center>
</body>
</html>

)=====";
 
void setup(void){

  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(LED_BUILTIN, HIGH);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
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
  server.on("/", [](){
    server.send(200, "text/html", Server_Page);
  });
  server.on("/gpio1-on", [](){
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/html", Server_Page);
  });

  server.on("/gpio1-off", [](){
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/html", Server_Page);
  });

  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");

}
 
void loop(void){
  //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
}
