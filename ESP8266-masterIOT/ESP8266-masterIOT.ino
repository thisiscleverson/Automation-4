
//library
#include <Arduino.h>
#include <Espalexa.h>
#include <Adafruit_NeoPixel.h>

//module
#include "lib/ESP_WiFiConfig.h"
#include "lib/WebControl.h"
#include "lib/sendIR.h"

//define
#define GPIO 0 
#define Npixels 30
#define pinSensor A0 // pin to sensor temperature

//set pin
#define ledStatus 2

///////////////////////////////////
Adafruit_NeoPixel pixels  (Npixels, GPIO, NEO_GRB + NEO_KHZ400); // configurar a fita de led
Espalexa ESPAlexa;

 
//variable
bool RainbowTurnON = false;
bool endRainbow = false;

//set function
void request(String command);
void startLedTape();
void setColor(byte R,byte G,byte B, byte index);
void Rainbow(int wait);

////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);   // serial 
  pixels.begin();         // Strip Led     
  SPIFFS.begin();         // SPIFFS
  IRsensor.begin();       // IR 

  pinMode(pinSensor, INPUT);
  pinMode(ledStatus, OUTPUT);

  //////////////////////////////////////////////
  
  startLedTape();   // strart led tape with cor blue
  readFilesHTML();  // read file HTLM
  connect_WiFi();   // connect to wifi
  addDevices();     // start communication with alexa 

  ESPAlexa.begin();
  server.begin();

  /////////////////////////////
  digitalWrite(ledStatus, LOW);
}

void loop() {

  String command = WebServer();
  if(command != ""){  
    request(command);
  }
  clearHeader();  

  if(RainbowTurnON == true){
    Rainbow(20);
  }
  
  //SensorTemp();   // sensor temperature  
  readSerial();     // read Serial commands 
  //ESPAlexa.begin();
  ESPAlexa.loop();  // esp Alexa Loop
  delay(1);
  
}

////////////////////////////////////////////////////////////////////////////////



/*
void SensorTemp(){
  static unsigned long beforeMillis;
  unsigned long currentMillis = millis();

  if(currentMillis - beforeMillis > 1000){ // wait 1m to add new value
     beforeMillis = currentMillis;
     
      float Values_analog = float(analogRead(pinSensor));
      float voltage = (Values_analog * 5) / 1023;
      float temp = voltage / 0.010;

      Serial.println("Temperatura do regulador: " + String(temp));
  } 
}*/
