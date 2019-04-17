
#include <SoftwareSerial.h>

SoftwareSerial TinySerial(3, 4); // RX, TX

int const clock = 2; //pino do arduino ligado ao clock do 74HC595
int const latch = 1; //pino do arduino ligado ao latch do 74HC595
int const data  = 0; //pino do arduino ligado ao data do 74HC595
int num[8]= {0,0,0,0,0,0,0,0};

void setup() {
  
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(data,OUTPUT);
  TinySerial.begin(9600);
}

void loop() {
numero();

if(TinySerial.available()){
  
int comando = TinySerial.read(); 
 num[comando-49] = !num[comando-49];
}

}

void numero(){
    digitalWrite(latch,LOW); //permite o fluxo dos dados.
       
    for (int x = 0; x <= 7; x++) {
      digitalWrite(clock,LOW); //pronto para receber o bit.
      
      if (num[x]) {
        digitalWrite(data,HIGH); //Grava o bit como 1
      } else {
        digitalWrite(data,LOW);  //Grava o bit como 0
      }
      
      digitalWrite(clock,HIGH); //grava o bit recebido.
    }    
    
    digitalWrite(latch,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.
   
}
