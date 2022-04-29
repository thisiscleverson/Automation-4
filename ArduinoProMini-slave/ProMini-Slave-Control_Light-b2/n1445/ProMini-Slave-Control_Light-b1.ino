/* 
 ┏━━━━━━━━━━━━━━━━━┓
 ┃ automação mini  ┃
 ┗━━━━━━━━━━━━━━━━━┛
   ass: Cleverson Emanuel Silva
 */

#include "lib/Start.h"
#include "lib/Button.h"

//pinos

#define button   2    // button
#define rele    A5    // rele
#define buzzer  6     // buzer
#define led_Blue 7    // led blue
#define frequencia 38 // khz


// variaveis [int]

int A_button;     // antes do botão
int D_button;     // depois do botão
int tempo    = 0; // tempo do rele no estado [ligado] 
int x        = 0; // valor do botão precionado
int sensorIR = 8; // pino para o sensor IR

// variaveis [bool]

bool estadoluz   = true;
bool contagem_on = false;
bool modoSoneca  = false;
bool liberarT    = false;
   
// variaveis [word]

word valorT = 20;  // <--- tempo em minutos
word tempoR  = 730;

// variaveis [long]

long timer  = 0;
long timer2 = 0;
long tempoL;

// variaveis [char]

char comando;


void setup() {
 Serial.begin(9600);

 valorT = valorT * 2;
 tempoL = tempoR * valorT;


  pinMode(rele, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led_Blue, OUTPUT);

  Before_button = digitalRead(button);

}


void loop() {
  /*
  butao();
  serial();
  funcao();
  relay();

  analogWrite(buzzer, 0);*/

}



void funcao(){

  tempo++;

   if(tempo >= 30){
        
        if(x == 1 && estadoluz == true){ // ligar por 30 minutos e desligar definidamente.
           estadoluz   = false;
           contagem_on = true;
           modoSoneca  = false;
           liberarT    = true;
           x = 0;
        }

        if(x == 1 && estadoluz == false){
            estadoluz   = true;
            contagem_on = false;
            modoSoneca  = false;
            liberarT    = true;
            x = 0;
        }

        if((x == 2) && (estadoluz == true)){  // ligar definidamente. 
            estadoluz   = false;
            modoSoneca  = false;
            contagem_on = false;
            liberarT    = false; 
            x = 0;
              
        }

        if ((x == 2) && (estadoluz == false)){
             estadoluz   = false;
             modoSoneca  = false;
             contagem_on = false;
             liberarT    = false; 
             x = 0;
               
        }

        if((x == 3) && (estadoluz == true)){
           estadoluz   = false;
           contagem_on = true;
           modoSoneca  = true;
           liberarT    = false;
           x = 0;
     

        }else if((x == 3) && (estadoluz == false)){
           estadoluz   = false;
           contagem_on = true;
           modoSoneca  = true;
           liberarT    = false;
           x = 0;    
            
        }
        
        tempo = 0;
        x     = 0;
   }

}

void relay(){

    if((contagem_on == true)  && (estadoluz == false)){ // <- contador (Luz ligada 30 minutos)
        timer++;
    }else if (contagem_on == false){
        timer = false;
    }

 
    if(timer == 2920 && estadoluz == false && modoSoneca == true){ // <-desligar a luz em 5 minutos->
        estadoluz = false;
        
        contagem_on  = false;
        modoSoneca   = false;
        timer        = false;
        liberarT     = true;
    }

    if((timer == tempoL) && (liberarT == true) && (modoSoneca == false)){ // <- [timer] luz desligar em 30 minutos
        contagem_on  = false;
        timer        = false;
        estadoluz    = true;

    }

    if(estadoluz == true){
        modoSoneca  = false;
        timer       = false;
    }

    digitalWrite(rele, estadoluz); // ----> desligar ou ligar a luz <-----
    //Serial.println(timer);
}