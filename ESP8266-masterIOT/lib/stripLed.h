#ifndef _stripLed_H
#define _stripLed_H
#include "WebServer.h"

class StripLed{

public:
	bool RainbowTurnON = false; // desligar o modo arco iris da fita de led 
	bool endRainbow = false;    

	int count = 0; // variavel para pegar a quantidade de pixel da fita de led 
	
	Adafruit_NeoPixel &pixels;

	StripLed(Adafruit_NeoPixel &ledPixels)
	:pixels(ledPixels)
	{
		count = pixels.numPixels(); // pegar a quantidade de pixels da fita de led
	}

	//função para iniciar a fita de led no setup
	void startStripLed(){
		for(int i=0; i<count; i++){
      		pixels.setPixelColor(i,pixels.Color(0,230,255));
      		pixels.show();
      		delay(500);
  		}
	}

	// função para alterna os modos da fita de led
	void setColor(byte R,byte G,byte B,bool index){
		switch(index){
	      case 0:
	         RainbowTurnON = false;
	         endRainbow = true;

	         for(int  i=0; i < pixels.numPixels(); i++){
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

	// função da fita de led para o modo arco iris
	void Rainbow(int wait){ 
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


};

#endif