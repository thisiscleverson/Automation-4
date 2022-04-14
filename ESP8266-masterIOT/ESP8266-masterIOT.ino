
/*
      Strip led 2.0 

      to: Cleverson Emanuel Silva -- 12/23/2021

*/
//library
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

//module
#include "lib/ESP_WiFiConfig.h"
#include "lib/WebServer.h"
#include "lib/stripLed.h"
///////////////////////////////////


IRsend IRsensor(4);



void setup() {
  Serial.begin(115200); // serial 
  pixels.begin();       // strip led  
  SPIFFS.begin();       // SPIFFS

  
  // turn on strip led in color blue
  for(int i=0; i<NumPixels; i++){
      pixels.setPixelColor(i,pixels.Color(0,230,255));
      pixels.show();
      //delay(500);
  }

  ///////////////////////////////////////////
  readFilesHTML();  // read file HTLM
  connect_WiFi();
}



void loop() {
  (redColor, 
  greenColor,
  blueColor,  
  value) = WebServer();

  //command(redColor, greenColor, blueColor, index);

  /*  
  if(RainbowTurnON == true){
    rainbowStripLed(10);
  }*/
 
}



