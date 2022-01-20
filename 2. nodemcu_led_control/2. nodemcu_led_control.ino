#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const char* ssid = "Wi-Fi ssid";
const char* password = "Wi-Fi password";
WiFiServer server(80);
void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, 0);
 Serial.println();
 Serial.print("Connecting to ");
 Serial.print(ssid);
 WiFi.begin(ssid, password);
 while(WiFi.status() != WL_CONNECTED){
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 server.begin(); 
 Serial.println("Server started");
 Serial.println(WiFi.localIP());
}
void loop() {
 WiFiClient client = server.available();
 if(!client){
   return;
 }
 Serial.println("New Client");
 while(!client.available()){
   delay(1);
 }
 String req = client.readStringUntil('\r');
 Serial.println(req);
 client.flush();
  int val;
 if (req.indexOf("/gpio/0") != -1){
   val = 0;
 }
 else if (req.indexOf("/gpio/1") != -1){
   val = 1;
 }
 else {
   Serial.println("invalid request");
   client.stop();
   return;
 }
 // Set GPIO2 according to the request
 digitalWrite(LED_BUILTIN, val);
 client.flush();
 String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
 s += (val)?"high":"low";
 s += "</html>";
Serial.println();
}
