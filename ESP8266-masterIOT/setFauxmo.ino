

EspalexaDevice* device; //this is optional




void addDevices(){

  device = new EspalexaDevice(DEVICE__1, light); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);                                 //this allows you to e.g. update their state value at any time!


  device = new EspalexaDevice(DEVICE__2, airConditioning); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);


  device = new EspalexaDevice(DEVICE__3, RainbowMode); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);


  device = new EspalexaDevice(DEVICE__4, ledTape); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);


  device = new EspalexaDevice(DEVICE__5, brightnees); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);


  device = new EspalexaDevice(DEVICE__6, airConditioning_18); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);


  device = new EspalexaDevice(DEVICE__7, airConditioning_23); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);


  device = new EspalexaDevice(DEVICE__8, setColorLadTape); //you can also create the Device objects yourself like here
  ESPAlexa.addDevice(device);                            //and then add them
  device->setValue(128);



}



void light(uint8_t state){
  if(state){
    Serial.write('T');
  }else{
    Serial.write('D');
  }
  
}


void airConditioning(uint8_t state){
    SendIR(0);
}


void RainbowMode(uint8_t state){
  if(state){
     RainbowTurnON = true;
     endRainbow    = false;
     Serial.println("Rainbow ON");
  }else{
     RainbowTurnON = false;
     endRainbow    = true;
     setColor(0, 0, 0, 1);
  }
}


void ledTape(uint8_t state){
   
   if(state){
      pixels.setBrightness(255);
      pixels.show();
   }else{
      pixels.setBrightness(0);
      pixels.show();
   }
  
}


void brightnees(uint8_t brightnees){
  pixels.setBrightness(brightnees);
  pixels.show();;
  
}


void airConditioning_18(uint8_t state){
    SendIR(1);
}


void airConditioning_23(uint8_t state){
    SendIR(2);
}


void setColorLadTape(uint8_t brightness, uint32_t rgb){
  
   int red,green,blue;
  
   red   = ((rgb >> 16) & 0xFF);
   green = ((rgb >>  8) & 0xFF);
   blue  = ((rgb & 0xFF));

   setColor(red, green, blue, 1);
  
}
