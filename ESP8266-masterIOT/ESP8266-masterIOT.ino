
/*
      Strip led 2.0 

      to: Cleverson Emanuel Silva -- 12/23/2021

*/
//library

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include "lib/ESP_WiFiConfig.h"
#include "lib/WebServer.h"
///////////////////////////////////


#define pin 3        // pin strip led
#define NumPixels 30 // number pixels of strip led

Adafruit_NeoPixel pixels(NumPixels, pin, NEO_GRB + NEO_KHZ400);
IRsend IRsensor(4);

/////////////////////////////////////

////////////////////////////////////
bool RainbowTurnON = false;
bool endRainbow =  false;

void setup() {
  Serial.begin(115200); // serial 
  pixels.begin();       // strip led  
  SPIFFS.begin();       // SPIFFS

  readFilesHTML();  // read file HTLM
  
  // turn on strip led in color blue
  for(int i=0; i<NumPixels; i++){
      pixels.setPixelColor(i,pixels.Color(0,230,255));
      pixels.show();
      //delay(500);
  }

  ///////////////////////////////////////////
  connect_WiFi();
}



void loop() {
  WebServer();

  if(RainbowTurnON == true){
    rainbowStripLed(10);
  }

}


void setColor(byte R,byte G,byte B,bool WM){
    switch(WM){
      case 0:
          RainbowTurnON = false;
          endRainbow = true;
         for(int  i=0; i < NumPixels; i++){
                pixels.setPixelColor(i,pixels.Color(R,G,B));
                pixels.show();
              }
      break;

      case 1:
          RainbowTurnON = true;
          endRainbow = false;
      break;
    }
}


void rainbowStripLed(int wait){
      for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
        for(int i=0; i < pixels.numPixels(); i++) {
          int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
          pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    } 
      WebServer();
      if(endRainbow == true){
        endRainbow = false;
        break;
      }      
      pixels.show(); // Update strip with new contents
      delay(wait); 
  }  
}





