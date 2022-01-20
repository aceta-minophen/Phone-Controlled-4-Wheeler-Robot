#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const char* ssid = "paya";
const char* password = "mishtynaina";
WiFiServer server(80);
void setup() {
 Serial.begin(115200);
 delay(10);
 Wire.begin(D1, D2);
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
 server.begin(); //Capital S???
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
   Wire.beginTransmission(8);
   Wire.write(val);
   Wire.endTransmission(); 
 }
 else if (req.indexOf("/gpio/1") != -1){
   val = 1;
   Wire.beginTransmission(8);
   Wire.write(val);
   Wire.endTransmission(); 
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
  Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
while(Wire.available()){
   char c = Wire.read();
 Serial.print(c);
}
Serial.println();
delay(1000);
}
