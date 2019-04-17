#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(7,8);//CSN,CE

void setup(){
  delay(150);
  //Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();
}


const int analogInPin = A0; // DIREÇÃO
int sensorValue = 0;
const int analogInPin2 = A1; // FRENTE E RÉ
int sensorValue2 = 0;





void loop(){
  
  sensorValue = analogRead(analogInPin); 
  sensorValue2 = analogRead(analogInPin2); 
  transmitter.txPL(sensorValue); // TRANSMITINDO VALORES
  transmitter.txPL(sensorValue2); // TRANSMITINDO VALORES
      
      transmitter.send(FAST);    //FUNÇÃO ACK DESATIVADA... PARA HABILITAR DIGITE SLOW
      
}
