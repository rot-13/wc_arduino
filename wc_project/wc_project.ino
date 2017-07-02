/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
 
void setup() {
  Serial.begin(115200);
//  Serial.setDebugOutput(true);
  delay(100);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 

void connect_wc() {
  HTTPClient http;

  String postData = "{\"content\":\"lalala\"}";
  String url = "http://pp-wc-172508.appspot.com/_ah/api/echo/v1/echo";

  Serial.print("connecting to ");
  Serial.println(url);

  http.begin(url);  
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.POST(postData);
  Serial.print("Response code ");
  Serial.println(httpCode);

  String payload = http.getString();
  Serial.print("Response: ");
  Serial.println(payload);

  http.end();
}


void loop() {
  delay(5000);

 connect_wc();
}
