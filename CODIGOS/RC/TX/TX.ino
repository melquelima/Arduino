#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(10,9);//CSN,CE

void setup(){
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();
  for (int j=2; j<9;j++){
    pinMode(j,INPUT_PULLUP);
  }
  
}

int comandos[9];

void loop(){
      get_values();
      transmitter.txPL(comandos,9);
      transmitter.send(SLOW);
     // delay(1);
}

void get_values(){
  comandos[0] = map(analogRead(A0),0,1023,0,178);
  comandos[1] = map(analogRead(A1),0,1023,0,255);
 // comandos[1] = analogRead(A1);
  comandos[2] = (!digitalRead(2)?!comandos[2]:comandos[2]);
  comandos[4] = (!digitalRead(4)?!comandos[4]:comandos[4]);
  while(!digitalRead(2) | !digitalRead(4)){}
  
  for (int j=3; j<8;j++){
   if (j!= 4)
    comandos[j] = !digitalRead(j); 
  }
  comandos[8] = !digitalRead(8);
}






