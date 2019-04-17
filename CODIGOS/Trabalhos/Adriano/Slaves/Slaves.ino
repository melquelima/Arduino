#include <mills.h>

#include <SPI.h>
#include <nRF24L01p.h>

mills tempo(200);

nRF24L01p receiver(5, 7); //CSN,CE

int rele = 9;
int addr = 2;

void setup() {
  tempo.inicio();
  pinMode(rele, OUTPUT);
  digitalWrite(rele, 0);
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
}
int valores[8];

void loop() {
  if (receiver.available()) {
    receiver.read();
    receiver.rxPL(valores, 8);
  }

 digitalWrite(rele,valores[addr-1]); 



  Serial.print(valores[0]);
  Serial.print(valores[1]);
  Serial.print(valores[2]);
  Serial.print(valores[3]);
  Serial.print(valores[4]);
  Serial.print(valores[5]);
  Serial.print(valores[6]);
  Serial.println(valores[7]);




}




