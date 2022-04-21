#ifndef _sendIR_H
#define _sendIR_H
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend IRsensor(4);

#define frequency 38

uint16_t rawData[] = {9050,4450, 600,1650, 600,1650, 600,550, 600,550, 600,500, 600,550, 600,550, 600,1650, 600,550, 600,1650, 600,1650, 600,550, 600,550, 550,600, 600,500, 650,500, 600,550, 600,550, 600,1650, 600,550, 550,550, 600,550, 650,500, 650,500, 600,550, 550,1700, 600,500, 600,550, 650,500, 600,550, 550,600, 600,550, 600,500, 600,550, 600,550, 600,550, 600,500, 600,550, 600,550, 600,550, 600,550, 600,500, 600,550, 600,550, 600,550, 600,500, 650,500, 600,550, 600};

void SendIR(){
    IRsensor.sendRaw(rawData,  sizeof(rawData) / sizeof(rawData[0]), frequency);  // Send a raw data capture at 38kHz.
    delay(50);
}

#endif