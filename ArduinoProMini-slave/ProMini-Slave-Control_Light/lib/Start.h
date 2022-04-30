#ifndef _Start_H
#define _Start_H

void Start(byte buzzer){
   
   analogWrite(buzzer, 250);
   delay(100);
   analogWrite(buzzer, 100);
   delay(50);
   delay(50);
   analogWrite(buzzer, 50);
   delay(50);
   analogWrite(buzzer, 250);
   delay(300);
   analogWrite(buzzer, 0); 
}

#endif