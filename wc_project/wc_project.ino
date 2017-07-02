/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

int buttonPin = 12;
int buttonPin2 = 14;
int LED = 13;
int InnerLed = 0;

bool state1 = false;
bool state2 = false;

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
   pinMode(buttonPin2, INPUT_PULLUP);
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
 

void postToServer(int cellNum, int state) {
  HTTPClient http;

  String stateString = (state == true) ? "0" : "1";
  String cellNumString = (cellNum == 1) ? "a" : "b";
  String url = "http://sinuous-client-172512.appspot.com/" + cellNumString + "/" + stateString;

  Serial.print("connecting to ");
  Serial.println(url);

  http.begin(url);  
  
  int httpCode = http.GET();
  Serial.print("Response code ");
  Serial.println(httpCode);

  String payload = http.getString();
  Serial.print("Response: ");
  Serial.println(payload);

  http.end();
}

void setState1(bool newState) {
  if (newState != state1) {
    state1 = newState;
    postToServer(1, state1);
  }
}

void setState2(bool newState) {
  if (newState != state2) {
    state2 = newState;
    postToServer(2, state2);
  }
}

void readButtonState() {
  Serial.println("Reading button state");
  // Read the value of the input. It can either be 1 or 0
  int buttonValue = digitalRead(buttonPin);
  if (buttonValue == LOW){
    // If button pushed, turn LED on
    digitalWrite(LED,HIGH);
    Serial.println("Button ON");
    setState1(true);
  } else {
    // Otherwise, turn the LED off
    digitalWrite(LED, LOW);
    Serial.println("Button OFF");
    setState1(false);
  }  

  int buttonValue2 = digitalRead(buttonPin2);
  if (buttonValue2 == LOW){
    // If button pushed, turn LED on
    digitalWrite(LED,HIGH);
    Serial.println("Button2 ON");
    setState2(true);
  } else {
    // Otherwise, turn the LED off
    digitalWrite(LED, LOW);
    Serial.println("Button2 OFF");
    setState2(false);
  }  

  if (state1 || state2) {
    digitalWrite(InnerLed, LOW);
  } else {
    digitalWrite(InnerLed, HIGH);
  }

  
  
}

void loop() {
  delay(1000);

  readButtonState();
}
