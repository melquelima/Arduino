#include <SPI.h>
#include <nRF24L01p.h>


int sensorValue;  // variável do potenciometro lido no TX (DIREÇÃO)

nRF24L01p receiver(7,8);//CSN,CE

void setup(){
  
  
  pinMode(4,OUTPUT);  // LED "OK"... INDICAÇÃO SE O PROGRAMA ESTA RODANDO
  digitalWrite(4,HIGH);
   
 
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
  Serial.begin(9600);
}


void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(sensorValue); // RECEBENDO VALOR
   
    Serial.println(sensorValue);
    
  }        
}
    
    
    
   
  
  
 
      
  
  
  

