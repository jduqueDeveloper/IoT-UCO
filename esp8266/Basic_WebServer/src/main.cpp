#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "credentials.h"
#include "web_page.h"

const char *ssid = SSID;
const char *password = PASSWORD;

const char *www_username = USER;
const char *www_password = USER_PASSWORD;

bool auth_req = false;

#define LOAD1 D1
#define LOAD2 D2

// WebServer Instantiation
ESP8266WebServer server(80);


// To control the loads according to the request
void handle_request(String argument, String value)
{

  int value_int = value.toInt();
  char LED[4] = "Led";
  char Load1[6] = "Load1";
  char Load2[6] = "Load2";

  if (argument == LED)
  {
    digitalWrite(LED_BUILTIN, !value_int);
    Serial.println("Led Changed");
  }

  if (argument == Load1)
  {
    digitalWrite(LOAD1, value_int);
    Serial.println("Load 1 Changed");
  }

  if (argument == Load2)
  {
    value_int = map(value_int, 0, 100, 0, 1024);
    analogWrite(LOAD2, value_int);
    Serial.println("Load 2 Changed");
  }
}


void setup(void)
{
  // "Import" Web page
  generate_page();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOAD1, OUTPUT);
  pinMode(LOAD2, OUTPUT);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Http Routes
  server.on("/", []() {
    if(auth_req==true){
      auth_req = false;
      return server.requestAuthentication();
    }
    
    if (!server.authenticate(www_username, www_password))
    {
      return server.requestAuthentication();
    }

    
    handle_request(server.argName(0), server.arg(0));
    server.send(200, "text/html", WebPage);
  });

  server.on("/LogOut", []() {
    auth_req = true;
    server.sendHeader("Location", "/",true); //Redirect to our html web page 
    server.send(307, "text/plane",""); 
  });


  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  // Handle client requests to web Server using .handleClient() 
  // method from ESP8266WebServer class
  server.handleClient();
}
