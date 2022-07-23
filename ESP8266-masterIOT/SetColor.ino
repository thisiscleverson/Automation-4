

void setColor(byte R,byte G,byte B, byte index){
    switch (index){
      case 1:
        pixels.setBrightness(255);
        pixels.show();
        RainbowTurnON = false;
	      endRainbow = true;

	      for(int  i=0; i < pixels.numPixels(); i++){
	          pixels.setPixelColor(i,pixels.Color(R,G,B));
	          pixels.show();
	      }
      break;
            
      case 2:
        pixels.setBrightness(255);
        pixels.show();
        RainbowTurnON = true;
        endRainbow = false;
      break;
  }
}
