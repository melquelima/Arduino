#include <TimerOne.h>

int A = A5, B = A4, C = A3;

int leds[6] = {
  0,0,0,0,0,0};
int ld[6][2] = {{A,B},{B,A},{B,C},{C,B},{A,C},{C,A}};


void setup() {
  Timer1.initialize(2500);
  Timer1.attachInterrupt( timerIsr );
}

int i =0;

void timerIsr(){
  apagaTudo();
  if(leds[i])led(i);
  i = (i==5?0:i+1);
}

void loop() {

  for(int j = 0;j<6;j++){
    leds[j] = !leds[j];
    delay(1000);  
  }


}

void led(int x){
  setar(ld[x][0],ld[x][1]);
  digitalWrite(ld[x][0],LOW);
  digitalWrite(ld[x][1],HIGH);
}

void apagaTudo(){
  pinMode(A,INPUT); 
  pinMode(B,INPUT);
  pinMode(C,INPUT); 
}

void setar (int w, int z){
  pinMode(w,OUTPUT); 
  pinMode(z,OUTPUT); 
}

