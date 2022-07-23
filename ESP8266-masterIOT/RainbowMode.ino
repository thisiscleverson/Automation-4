


void Rainbow(int wait){
  
   for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i < pixels.numPixels(); i++) {
          int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
          pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    		} 

      	 String command = WebServer(); 
         request(command);
         clearHeader();
         readSerial(); 
         ESPAlexa.loop();  // esp Alexa Loop          

	    	if(endRainbow == true){  // finish led tape
        		endRainbow = false;
        		break;
      		}  
     		  pixels.show(); // Update strip with new contents
      		delay(wait); 
  		}   
}
