#include <ESP8266WiFi.h>

#include "WemoSwitch.h"
#include "WemoManager.h"
#include "CallbackFunction.h"


#define  REDPIN 14
#define  GREENPIN 4
#define  BLUEPIN 5

// prototypes
boolean connectWifi();

//on/off callbacks
void redlightOn();
void redlightOff();
void bluelightOn();
void bluelightOff();
void greenlightOn();
void greenlightOff();



//------- Replace the following! ------
char ssid[] = "xxxxxxxxx";       // your network SSID (name)
char password[] = "xxxxxxxx";          // your network key

WemoManager wemoManager;
WemoSwitch *redlight = NULL;
WemoSwitch *bluelight = NULL;
WemoSwitch *greenlight = NULL;

const int ledPin = BUILTIN_LED;

void setup()
{
  Serial.begin(115200);

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  // analogWrite(REDPIN, 1024);
  // analogWrite(GREENPIN,0);
  // analogWrite(BLUEPIN,0);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  wemoManager.begin();
  // Format: Alexa invocation name, local port no, on callback, off callback
  redlight = new WemoSwitch("red light", 80, redlightOn, redlightOff);
  bluelight = new WemoSwitch("blue light", 81, bluelightOn, bluelightOff);
  greenlight =  new WemoSwitch("green light", 82, greenlightOn, greenlightOff);
  wemoManager.addDevice(*redlight);
  wemoManager.addDevice(*bluelight);
  wemoManager.addDevice(*greenlight);

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // Wemos BUILTIN_LED is active Low, so high is off
}

void loop()
{
  wemoManager.serverLoop();
}

void redlightOn() {
    Serial.print("redlightOn ...");
    digitalWrite(ledPin, LOW);
    analogWrite(REDPIN, 1024);
    analogWrite(GREENPIN,0);
    analogWrite(BLUEPIN,0);
}

void redlightOff() {
    Serial.print("redlightOff ...");
    digitalWrite(ledPin, HIGH);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN,0);
    analogWrite(BLUEPIN,0);
}

void bluelightOn() {
    Serial.print("bluelightOn...");
    digitalWrite(ledPin, LOW);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN,0);
    analogWrite(BLUEPIN,1024);
}

void bluelightOff() {
    Serial.print("bluelightOff ...");
    digitalWrite(ledPin, HIGH);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN,0);
    analogWrite(BLUEPIN,0);
}

void greenlightOn(){
    Serial.print("greenlightOn...");
    digitalWrite(ledPin, LOW);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN,1024);
    analogWrite(BLUEPIN,0);
}

void greenlightOff(){
    Serial.print("greenlightOff...");
    digitalWrite(ledPin, HIGH);
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN,0);
    analogWrite(BLUEPIN,0);
}

