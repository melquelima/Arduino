
#include <Dsp74bit.h>
#include <mills.h>
Dsp74bit disp(2,3,4,5);
mills tempo(400);

int num[4] = {1,2,3,4};
int atual = 1;

 

void setup() {
pinMode(6,OUTPUT); 
digitalWrite(6,LOW);
tempo.inicio();
disp.show(num[0]);

}

void loop() {

    if(tempo.verifica()){
      clock();
      disp.show(num[atual]);
      atual = (atual == 3?0:atual+1);
    }  
}



void clock(){
      digitalWrite(6,HIGH);
      delayMicroseconds(500);
      digitalWrite(6,LOW);
}
