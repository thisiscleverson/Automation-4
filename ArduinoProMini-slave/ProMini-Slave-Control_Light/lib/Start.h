#ifndef _Start_H
#define _Start_H

void Start(byte buzzer){
  analogWrite(buzzer, 250);
  delay(900);
  analogWrite(buzzer,122);
  delay(500);
  analogWrite(buzzer,50);
  delay(900);
  analogWrite(buzzer,0);
}

#endif