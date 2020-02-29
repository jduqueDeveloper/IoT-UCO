#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#define INP_3 D3

// Replace with your network credentials
//const char* ssid = "IoT-UCO";
//const char* password = "LifeisIoT";

const char* ssid = "IoT-UCO";
const char* password = "LifeisIoT";


// WebServer Instantiation
ESP8266WebServer server(80);

//Web Page Variable
String webPage1 = "";
String webPage2 = "";
String webPage3 = "";

const char* www_username = "admin";
const char* www_password = "esp8266";

void setup(void){
  
  //Build Basic Web Page using HTML
  webPage1 += "<h1>ENCENDER Y APAGAR LED</h1>";
  webPage1 += "<p><marquee>######.....IoT Rulz!!!.....######</marquee></p>";
  webPage1 += "<a href='""/encender""' class='btn btn-default'>Encender LED</a>";
  webPage1 += "<hr>";
  webPage1 += "<a href='""/apagar""' class='btn btn-default'>Apagar LED</a>";
  //webPage1 += "<a href='"+ WiFi.localIP().toString()+""+"/verde"+"' class='btn btn-default'>Go to Google</a>";
  webPage2 += "<h1>AMAZING WEB SERVER</h1>";
  webPage2 += "<p><marquee>######.....IoT Rulz!!!.....######</marquee></p>";
  //webPage2 += "<body style='background-color:green;'>";
  //webPage2 += "<button type='button' class='btn'>Basic</button>";
  webPage3 += "<h1>AMAZING WEB SERVER</h1>";
  webPage3 += "<p><marquee>######.....IoT Rulz!!!.....######</marquee></p>";
  
  delay(1000);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(INP_3,INPUT);

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
     if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/html", webPage1);
  });
  server.on("/encender", [](){
  if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/html", webPage1);
  });

   server.on("/apagar", [](){
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(LED_BUILTIN, HIGH);
    
    server.send(200, "text/html", webPage1);
  });
  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");

}
 
void loop(void){
  //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
}
