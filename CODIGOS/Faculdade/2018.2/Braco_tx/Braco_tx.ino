#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(7,8);//CSN,CE

void setup(){
  delay(150);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(80);
  transmitter.TXaddress("Artur");
  transmitter.init();
  pinMode(A5,INPUT_PULLUP);
}

byte myData[7]={90,90,90,90,90,90,180};

void loop(){
  
  
  //myData[0] = map(analogRead(A1),0,1023,0,180);
  //myData[1] = map(analogRead(A1),0,1023,180,0);
  //myData[3] = !digitalRead(A5);
  
  myData[3] = map(analogRead(A1),0,1023,0,180); // ok - Angulo 3
  myData[5] = map(analogRead(A3),0,1023,0,180); // ok - BASE
  myData[2] = map(analogRead(A0),0,1023,180,0); // ok - Angulo 2
  myData[0] = map(analogRead(A2),0,1023,0,180); // ok - Angulo 1
  myData[1] = map(analogRead(A2),0,1023,180,0); // ok - Angulo 1
  myData[4] = map(analogRead(A4),0,1023,0,180); // ok - Angulo 4
  myData[6] = digitalRead(A5)?70:150;
  
  transmitter.txPL(myData,7);
  transmitter.send(FAST);  
  
  
}
