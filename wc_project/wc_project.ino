/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

int buttonPin = 12;
int LED = 13;
int InnerLed = 0;

void setupWifi() {
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

void setupButton() {
   // Define pin #12 as input and activate the internal pull-up resistor
   pinMode(buttonPin, INPUT_PULLUP);
}

void setupLeds() {
  pinMode(InnerLed, OUTPUT);
  // Define pin #13 as output, for the LED
//  pinMode(LED, OUTPUT);  
}

void setup() {
  Serial.begin(115200);
//  Serial.setDebugOutput(true);
  delay(100);

  setupWifi();
  setupButton();
  setupLeds();
}
 

void postToServer() {
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

void readButtonState() {
  Serial.println("Reading button state");
  // Read the value of the input. It can either be 1 or 0
  int buttonValue = digitalRead(buttonPin);
  if (buttonValue == LOW){
    // If button pushed, turn LED on
    digitalWrite(LED,HIGH);
    Serial.println("Button ON");
    digitalWrite(InnerLed, LOW);
//    postToServer();
  } else {
    // Otherwise, turn the LED off
    digitalWrite(LED, LOW);
    Serial.println("Button OFF");
    digitalWrite(InnerLed, HIGH);
  }  
}

void loop() {
  delay(1000);

  readButtonState();
}
