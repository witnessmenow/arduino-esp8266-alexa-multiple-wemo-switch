#include <ESP8266WiFi.h>

#include "WemoSwitch.h"
#include "WemoManager.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

//on/off callbacks
void switch1On();
void switch1Off();
void switch2On();
void switch2Off();

//#####################################################################
//########## config your switch here ##################################
//#####################################################################

const char ssid[] = "xxx";      // your network SSID (name)
const char password[] = "yyyy"; // your network key

const char switch1Name[] = "xyz1";  // Alexa Name of the first Switch
const int switch1Pin = 1;   // Switch 1 Pin
  
const char switch2Name[] = "xyz2";  // Alexa Name of the second Switch
const int switch2Pin = 2;   //Switch 2 Pin

//#####################################################################
//########## end of config area #######################################
//#####################################################################

WemoManager wemoManager;
WemoSwitch *switch1 = NULL;
WemoSwitch *switch2 = NULL;

const int ledPin = BUILTIN_LED;

void setup()
{
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  pinMode(switch1Pin, OUTPUT); // initialize digital switch1Pin as an output.
  pinMode(switch2Pin, OUTPUT); // initialize digital switch2Pin as an output.
  
  delay(100);
  
  digitalWrite(ledPin, HIGH); // Wemos BUILTIN_LED is active Low, so high is off
  digitalWrite(switch1Pin, HIGH); // Wemos switch1Pin is active Low, so high is off
  digitalWrite(switch2Pin, HIGH); // Wemos switch2Pin is active Low, so high is off 
  
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
    if(digitalRead(BUILTIN_LED)==LOW){
        digitalWrite(BUILTIN_LED, HIGH);
      }else{
        digitalWrite(BUILTIN_LED, LOW);
      }
    }
  digitalWrite(ledPin, LOW);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  wemoManager.begin();
  // Format: Alexa invocation name, local port no, on callback, off callback
  switch1 = new WemoSwitch(switch1Name, 80, switch1On, switch1Off);
  switch2 = new WemoSwitch(switch2Name, 81, switch2On, switch2Off);
  wemoManager.addDevice(*switch1);
  wemoManager.addDevice(*switch2);
}

void loop()
{
  wemoManager.serverLoop();
}

void switch1On() {
    Serial.print("Switch 1 turn on ...");
    digitalWrite(switch1Pin, LOW);
}

void switch1Off() {
    Serial.print("Switch 1 turn off ...");
    digitalWrite(switch1Pin, HIGH);
}

void switch2On() {
    Serial.print("Switch 2 turn on ...");
    digitalWrite(switch2Pin, LOW);
}

void switch2Off() {
    Serial.print("Switch 2 turn off ...");
    digitalWrite(switch2Pin, HIGH);
}
