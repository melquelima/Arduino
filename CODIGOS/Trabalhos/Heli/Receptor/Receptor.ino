#include <SPI.h>
#include <nRF24L01p.h>


int sensorValue;  // variável do potenciometro lido no TX (DIREÇÃO)
int sensorValue2;
nRF24L01p receiver(9,10);//CSN,CE
int led = 2;
int led2 = 3;
void setup(){
  
  
  pinMode(4,OUTPUT);  // LED "OK"... INDICAÇÃO SE O PROGRAMA ESTA RODANDO
  digitalWrite(4,HIGH);
   
 pinMode(led,OUTPUT);
 pinMode(led2,OUTPUT);
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
    receiver.rxPL(sensorValue2);
    Serial.print(sensorValue);
    Serial.println(sensorValue2);
  }else{
    sensorValue = 0;
    sensorValue2=0;
  }
  if(sensorValue)
   digitalWrite(led,HIGH); 
  else digitalWrite(led,LOW);
  
  
    if(sensorValue2)
   digitalWrite(led2,HIGH); 
  else digitalWrite(led2,LOW);

  
}
    
    
    
   
  
  
 
      
  
  
  

