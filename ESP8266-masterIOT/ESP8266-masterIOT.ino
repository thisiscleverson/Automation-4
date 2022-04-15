
/*
      Strip led 2.0 

      to: Cleverson Emanuel Silva -- 12/23/2021

*/
//library
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <Adafruit_NeoPixel.h>
#include <IRsend.h>

//module
#include "lib/ESP_WiFiConfig.h"
#include "lib/WebServer.h"
#include "lib/stripLed.h"
///////////////////////////////////

IRsend IRsensor(4);

#define pin 3
#define Npixels 30

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(Npixels, pin, NEO_GRB + NEO_KHZ400); // configurar a fita de led

StripLed stripled(pixels);

void setup() {
  Serial.begin(115200); // serial 
  pixels.begin();        // Strip Led     
  SPIFFS.begin();       // SPIFFS

  /*
  // turn on strip led in color blue
  for(int i=0; i<NumPixels; i++){
      pixels.setPixelColor(i,pixels.Color(0,230,255));
      pixels.show();
      //delay(500);
  }*/

  ///////////////////////////////////////////
  stripled.startStripLed();  
  //readFilesHTML();  // read file HTLM
  //connect_WiFi();
}



void loop() {
  /*
  (redColor, 
  greenColor,
  blueColor,  
  value) = WebServer();*/

  //command(redColor, greenColor, blueColor, index);

  
  if(stripled.RainbowTurnON == true){
    //rainbowStripLed(10);
  }
 
}



