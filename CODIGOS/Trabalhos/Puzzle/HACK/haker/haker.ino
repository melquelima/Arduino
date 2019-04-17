#include <EEPROM.h>
int rele1 =A4;
int rele2 =A1;
int rele3 =11;
int led = A5;
int tempo =(EEPROM.read(1)==0?500:EEPROM.read(1)*1000);
boolean entra = true;

void setup(){
  pinMode(rele1,OUTPUT);
  pinMode(rele2,OUTPUT);
  pinMode(rele3,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,0);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()>0){
    int comando = Serial.read();
    switch (comando){
    case '1':
      digitalWrite(rele1,1);
      break;
    case '2':
      digitalWrite(rele2,1);
      break;
    case '3':
      digitalWrite(rele3,1);
      break;
    case 'C':
      entra = false;
      delay(200);
      comando = Serial.read();
      if (comando>='0' && comando <='9'){
        tempo = comando=='0'?500:(comando-48)*1000;
        EEPROM.write(1,comando-48);
        Serial.println(tempo);
      }
      else{
        Serial.println("ERROR"); 
      }
    default:
      entra = false;    
    }

    if (entra){
      delay(tempo);
      Serial.println((char)comando);
      digitalWrite(rele1,0);
      digitalWrite(rele2,0);
      digitalWrite(rele3,0);
    }
   entra = true; 
  }
}

