#include <SPI.h>
#include <nRF24L01p.h>

#include "Servo.h"
Servo servoMotorObj; //Criando um objeto da classe Servo
int const servoMotorPin    = 10;  //pino digital associado ao controle do servomotor

int sensorValue;  // variável do potenciometro lido no TX (DIREÇÃO)
int sensorValue2; // variável do potenciometro lido no TX (FRENTE E RÉ)
int frente;
int re;

nRF24L01p receiver(7,8);//CSN,CE

void setup(){
  
  analogWrite(6,0);
  
  delay(150);
  
  pinMode(4,OUTPUT);  // LED "OK"... INDICAÇÃO SE O PROGRAMA ESTA RODANDO
  digitalWrite(4,HIGH);
  pinMode(2,OUTPUT); // PORTA PARA SELECIONAR FRENTE OU RÉ 
  
  servoMotorObj.attach(servoMotorPin); //associando o pino digital ao objeto da classe Servo
 

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
}


void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(sensorValue); // RECEBENDO VALOR
    receiver.rxPL(sensorValue2); // RECEBENDO VALOR
   
      
                     // SERVO MOTOR*****************
    sensorValue= map(sensorValue, 0, 1023, 45, 135);//mapeando o valor para a escala do servo (entre 0 e 180)
    servoMotorObj.write(sensorValue); //definindo o valor/posição do servomotor
    
  //**********************************************************************************************************************
    
                     // MOTOR DC*******************************
    
    
          // FRENTE....................
          
    if( sensorValue2 > 532){
    
    frente = map(sensorValue2, 532, 1023, 0,250 );
    
    analogWrite (6,frente);
    
    digitalWrite(2,LOW);
    }
    
    //........................................
    
     if( sensorValue2 > 490 and sensorValue2 < 528){
       
       delay (50);
       
       digitalWrite(2,LOW);
       
       delay(20);
       
       analogWrite(6,0);
       
       
       
     
       
       
     }
    
    
    
    
    
                    // RÉ.................
    
    if( sensorValue2 < 480){
    
    re = map(sensorValue2, 480, 0, 0,30 );
    
    
    digitalWrite(2,HIGH);
    delay(40);
    analogWrite (6,re);
   
     
   
    
    
    
  }
  //.................................................
  
  //***************************************************************************
}
}
    
    
    
   
  
  
 
      
  
  
  

