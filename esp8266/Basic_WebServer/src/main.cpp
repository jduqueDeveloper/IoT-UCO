#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// Replace with your network credentials
const char* ssid = "SEA UCO";
const char* password = "SeaUco666";
// WebServer Instantiation
ESP8266WebServer server(80);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

String header;

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

const char Server_Page[] PROGMEM = R"=====(
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    body {
      text-align: center;
      font-family: "Trebuchet MS", Arial;
      margin-left:auto;
      margin-right:auto;
    }
    .slider {
      width: 300px;
    }

    .button{
    color: white
    padding: 20px 34px;
    text-aling: center;
    font-size: 20px;
    margin: 4px 2px;
    cursor: pointer;
  }
  </style>





<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head>
<body>
<h1>ESP8266 with Servo</h1>
<form>
  <button type = "submit" formaction = "/led-on">Click me to do magic!</button>
  <button type = "submit" formaction = "/led-off">Click me to finish the magic!</button>
</form>
  <p>Position: <span id="servoPos"></span></p>
  <input type="range" min="0" max="180" class="slider" id="servoSlider" onchange="servo(this.value)"/>
  <script>
    var slider = document.getElementById("servoSlider");
    var servoP = document.getElementById("servoPos");
    servoP.innerHTML = slider.value;
    slider.oninput = function() {
      slider.value = this.value;
      servoP.innerHTML = this.value;
    }
    $.ajaxSetup({timeout:1000});
    function servo(pos) {
      $.get("/?value=" + pos + "&");
      {Connection: close};
    }
  </script>
</body>
</html>

)=====";
 
void setup(void){

  myservo.attach(13); 

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
  server.on("/led-on", [](){
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/html", Server_Page);
  });

  server.on("/led-off", [](){
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

  //GET /?value=180& HTTP/1.1
  if(header.indexOf("GET /?value=")>=0) {
    pos1 = header.indexOf('=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);
              
    //Rotate the servo
    myservo.write(valueString.toInt());
    Serial.println(valueString); 
  } 

}
