
/* 
 ┏━━━━━━━━━━━━━━━━━┓
 ┃automação mini   ┃
 ┗━━━━━━━━━━━━━━━━━┛

   ass: Cleverson Emanuel Silva

 */
//module
#include "lib/Start.h"

//pinos

#define button   9    // button
#define relay    8    // rele
#define buzzer   11   // buzer
#define led_Blue 7    // led blue
 
#define FET 2 // function execution time in second   2s = 2000ms  
#define TimerLight 25 // timer to turn on the light


// variaveis [int]
int before_button;     // antes do botão
int after_button;     // depois do botão

int function;

unsigned long beforeMillis;
unsigned long beforeMillisRelay;


bool turnONTimerLight = false;
bool turnONtheLight = false;


void setup() {
  Serial.begin(115200);

  pinMode(relay, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led_Blue, OUTPUT);

  before_button = digitalRead(button);

  Start(buzzer); // start with song
}


void loop() {
  
  Button();
  CommunicationSerial();
  Function();
  
  //Serial.println("Timer: " + String(turnONTimerLight));
 // Serial.println("Lighty: " + String(turnONtheLight));

}

void Button(){

  after_button = digitalRead(button);

  if((before_button == true) && (after_button == false)){
      function++;
      beforeMillisRelay = millis();
      analogWrite(buzzer, 200);
  }

  before_button = digitalRead(button);

  if(function > 4){
      function = 0;

      analogWrite(buzzer, 250);
      delay(500);
      analogWrite(buzzer, 0);
  }

  delay(30);
  analogWrite(buzzer, 0);
  
}

void Function(){

  unsigned long currentMillis = millis();  

  if((currentMillis - beforeMillisRelay) > 500){ // wait 2s to add new value
     beforeMillisRelay = currentMillis;
     
     switch(function){
       case 1:
          //turnONtheLight   = !turnONtheLight;
          if(turnONtheLight == false){
             turnONTimerLight = !turnONTimerLight; // turn on the light with timer of 30 min 
          } 
          turnONtheLight   = !turnONtheLight;
       	  if(turnONtheLight == false){
             turnONTimerLight = !turnONTimerLight; // turn on the light with timer of 30 min 
          } 
          digitalWrite(relay, turnONtheLight);
          function = 0;
       break;

       case 2:
          turnONtheLight = true;
          digitalWrite(relay, turnONtheLight);
          function = 0;
       break;   

       function = 0;
     }      
  }
  
  if((turnONTimerLight) && (turnONtheLight) && (Timer(false) >= TimerLight)){
    turnONtheLight = !turnONtheLight;
    digitalWrite(relay, turnONtheLight);
    Timer(true); // timer = 0      
    turnONTimerLight = !turnONTimerLight;          
  }
  else if((!turnONTimerLight) && (!turnONtheLight) && (Timer(false) > 0)){
    Timer(true); //timer = 0
  } 
  
  if(turnONtheLight == false){  // disable timer 
   	 turnONTimerLight = false;
  }
}

void CommunicationSerial(){
  if(Serial.available() > 0){
    if(Serial.readString() == "LTOx22"){
      function = 2;
    }
  }
}

unsigned long Timer(bool rest){  // timer
  static int timer;
  
  if(rest){
    timer = 0;
    return 0;
  }

  if(timer > 40){
    timer = 0;
  }
 
  unsigned long currentMillis = millis();

  if(currentMillis - beforeMillis > 60000){ // wait 1m to add new value
     timer++; // add 1 value to variable
     beforeMillis = currentMillis;
     //Serial.println("function millis okay!");
  }
  return(timer);
}
