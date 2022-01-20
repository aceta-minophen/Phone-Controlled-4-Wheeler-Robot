#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>

const char* ssid = "Wi-Fi name";
const char* password = "password";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  Wire.begin(D1, D2); 
  
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
  req.replace("+", " ");          // Spaces without +
  req.replace(" HTTP/1.1", "");   // this delete HTTP/1.1
  req.replace("GET /", "");   
  int val = req.toInt();

  byte buffer[10];
  buffer[0] = lowByte(val);
  buffer[1] = highByte(val);

  Serial.println(val);
  Wire.beginTransmission(8);
  Wire.write(buffer, 2);
  Wire.endTransmission();
  
  
  client.flush();

}
