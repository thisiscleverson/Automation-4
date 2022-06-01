
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
#define led_Blue 13   // led blue
 
#define FET 2 // function execution time in second   2s = 2000ms  
#define TimerLight 10 // timer to turn on the light


// variaveis [int]
int before_button;     // antes do botão
int after_button;     // depois do botão

int function;

unsigned long beforeMillis;
unsigned long beforeMillisRelay;
unsigned long beforeMillisButton;


bool turnONTimerLight = false;  // timer on or off
bool turnONtheLight   = false; //  light on or off


void setup() {
  Serial.begin(115200);

  pinMode(relay, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led_Blue, OUTPUT);

  before_button = digitalRead(button);

  Start(buzzer); // start with song

  Serial.println("Arduino OK");
}


void loop() {
  ReadSerial();
  Button();
  Function();
  
}

void ReadSerial(){
  char c;
  if(Serial.available() > 0){

     c = Serial.read();
     switch(c){
        case 'L':
          function = 3;
          Function();
        break;

     }
  }
}

void Button(){
  unsigned long currentMillis = millis();
  static bool action_once;

  after_button = digitalRead(button);

  if((before_button == true) && (after_button == false)){
      function++;
      beforeMillisRelay = millis();
      analogWrite(buzzer, 200);
  }
  else if((!before_button) && (!after_button)){ // turn on the air conditioning
      if((currentMillis - beforeMillisButton > 700) && (action_once)){ // wait 2s 
         action_once = false;
         Serial.write("A");
         delay(100);
         analogWrite(buzzer,200);
         delay(400);
         function = 1;
         Function();        
         beforeMillisButton = currentMillis;
        }
  }
  else{
     beforeMillisButton = currentMillis;
     action_once = true;    
  }

//////////////////////////////////////////////////////////////////////////////////////////////

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
          /*if(turnONtheLight == false){
             turnONTimerLight = !turnONTimerLight; // turn on the light with timer of 30 min 
          } 
          turnONtheLight = !turnONtheLight;
       	  if(turnONtheLight == false){
             turnONTimerLight = !turnONTimerLight; // turn on the light with timer of 30 min 
          } */

          turnONtheLight = !turnONtheLight;
          if(turnONtheLight == true){
             turnONTimerLight = true;
          }
          else{
             turnONTimerLight = false;
          }

          digitalWrite(relay, turnONtheLight);
          function = 0;
       break;

       case 2:
          turnONtheLight = true;
          digitalWrite(relay, turnONtheLight);
          analogWrite(buzzer,200);
          delay(500);
          function = 0;
       break;

       case 3:
          turnONtheLight = !turnONtheLight;
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
