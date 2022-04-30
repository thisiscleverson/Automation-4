#ifndef _Button_H
#define _Button_H

byte After_button;
byte Before_button;
byte function;

int Button(byte buzzer, byte button){
	
  After_button = digitalRead(button);

  if((Before_button == true) && (After_button == false)){
      function++;
      //time = 0;
      analogWrite(buzzer, 200);
      delay(500);
      analogWrite(buzzer,0);
  }

  Before_button = digitalRead(button);

  if(function > 4){
      function = 0;
      analogWrite(buzzer, 250);
      delay(500);
      analogWrite(buzzer, 0);
  }

  delay(30);

  return (function);
}

#endif