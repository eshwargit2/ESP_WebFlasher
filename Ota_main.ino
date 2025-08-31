//ESP Web Flasher using in Browser
//Follow the github page "eshwargit2"
//github link :"https://github.com/eshwargit2/ESP_WebFlasher.git"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include "ota_html.h" 

const char* ssid = "Eshwar Creativity "; //your SSID 
const char* password = "666666555"; //your password

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

const int ledPin = 2;
bool ledState = false;



void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

void handleLedOn() {
  digitalWrite(ledPin, LOW); 
  server.send(200, "text/plain", "LED is ON");
}

void handleLedOff() {
  digitalWrite(ledPin, HIGH); 
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  httpUpdater.setup(&server, "/update");

  server.on("/update", HTTP_GET, []() {
    server.send_P(200, "text/html", MAIN_page);
  });

  server.on("/", handleRoot);
  
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
