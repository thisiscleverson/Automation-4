


void startLedTape(){
  pixels.setBrightness(255);
  pixels.show();
  for(int i=0; i<pixels.numPixels(); i++){
      pixels.setPixelColor(i,pixels.Color(0,230,255));
      pixels.show();
      delay(250);
  }
}
