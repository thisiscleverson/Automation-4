
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
#include "lib/WebServer2.h"
#include "lib/stripLed.h"
///////////////////////////////////

IRsend IRsensor(4);

#define pin 3
#define Npixels 30

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(Npixels, pin, NEO_GRB + NEO_KHZ400); // configurar a fita de led

StripLed stripled(pixels);

webserver Web_server(pixels);



void setup() {
  Serial.begin(115200); // serial 
  pixels.begin();        // Strip Led     
  SPIFFS.begin();       // SPIFFS

  ///////////////////////////////////////////
  //stripled.startStripLed(); 

  //ws readFilesHTML();  
  
  Web_server.readFilesHTML();  // read file HTLM
  connect_WiFi();

}



void loop() {

  Web_server.WebServer();

    
  Serial.println(RainbowTurnON,endRainbow);  
  /*
  (redColor, 
  greenColor,
  blueColor,  
  value) = WebServer();*/

  //command(redColor, greenColor, blueColor, index);
  
  if(RainbowTurnON == true){
    stripled.Rainbow(10);
  }
 
}



