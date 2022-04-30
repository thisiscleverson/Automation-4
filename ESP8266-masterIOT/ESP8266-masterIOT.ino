
//library
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

//module
#include "lib/ESP_WiFiConfig.h"
#include "lib/WebControl.h"
#include "lib/sendIR.h"

//define
#define pin 3
#define Npixels 30

///////////////////////////////////
Adafruit_NeoPixel pixels  (Npixels, pin, NEO_GRB + NEO_KHZ400); // configurar a fita de led
//IRsend IRsensor(4);
 
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
  IRsensor.begin();

  //////////////////////////////////////////////
  
  startLedTape();   // strart led tape with cor blue
  readFilesHTML();  // read file HTLM
  connect_WiFi();   // connect to wifi

}

void loop() {

  String command = WebServer();
  if(command != ""){  
    request(command);
  }
  clearHeader();  

  if(RainbowTurnON == true){
    Rainbow(10);
  }
 
}

//commands

void request(String command){        
        if(command.indexOf("GET /ESPIOT?r") >= 0){
            int pos1 = command.indexOf('r'); //red
            int pos2 = command.indexOf('g'); // green
            int pos3 = command.indexOf('b'); // blue
            int pos4 = command.indexOf('&');

            int red   = command.substring(pos1+1, pos2).toInt();
            int green = command.substring(pos2+1, pos3).toInt();
            int blue  = command.substring(pos3+1, pos4).toInt();

            setColor(red,green,blue,1);            
        }

        else if(command.indexOf("GET /ESPIOT?") >= 0){
            int pos = command.indexOf('?');
            int finally = command.indexOf('&');

            String command2 = command.substring(pos+1,finally); //to commands
            
            //////////////////////////////////////////////////////////////////////////

            if(command2 == "RainbowON"){ // turn on rainbow mode
                setColor(0,0,0,2);
            }   
            else if(command2 == "Light"){ // turn on or off the light
                Serial.write("LTOx22");
                delay(100);
            }
            else if(command2 == "airConditioning"){ //turn on air conditioning
                SendIR();
            }
        } 
}

void startLedTape(){
  for(int i=0; i<pixels.numPixels(); i++){
      pixels.setPixelColor(i,pixels.Color(0,230,255));
      pixels.show();
      delay(250);
  }
}

void setColor(byte R,byte G,byte B, byte index){
    switch (index){
      case 1:
        //Serial.println("dentro do case 1");
        RainbowTurnON = false;
	      endRainbow = true;

	      for(int  i=0; i < pixels.numPixels(); i++){
	          pixels.setPixelColor(i,pixels.Color(R,G,B));
	          pixels.show();
	      }
      break;
            
      case 2:
        RainbowTurnON = true;
        endRainbow = false;
      break;
  }
}

void Rainbow(int wait){
  
   for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i < pixels.numPixels(); i++) {
          int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
          pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    		} 

      	 String command = WebServer(); 
         request(command);

	    	if(endRainbow == true){  // finish led tape
        		endRainbow = false;
        		break;
      		}  
     		  pixels.show(); // Update strip with new contents
      		delay(wait); 
  		}   
}
