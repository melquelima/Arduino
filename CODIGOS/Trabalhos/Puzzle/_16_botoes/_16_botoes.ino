/*
Biblioteca feita por Melque_lima.
Obs: os endereços sempre em numeros inteiros
*/


#include <pcfXpand.h>
#include <Wire.h> 
#include <EEPROM.h> 

pcfXpand pcf(32,INPUT); // endereço do CI a ser lido
pcfXpand pcf2(39,INPUT); // endereço do CI a ser lido

int senha[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
int digitado[16];
int grava = 2;
int rele = 13;
int buzzer = 12;

void setup() {
Serial.begin(9600);
pinMode(grava,INPUT_PULLUP);
pinMode(rele,OUTPUT);
pinMode(buzzer,OUTPUT);

for(int i = 0;i<16;i++){
    senha[i] = EEPROM.read(i+1);
    Serial.print(senha[i]);
  }
  Serial.println();

if(!pcf.begin() || !pcf2.begin()){
 Serial.println("ERROR");
   for(int i = 0;i<10;i++){
    bip_but();
   delay(100); 
   }
 while(1){} 

}
 Serial.println("OK");
}

void loop() {
  
  if (igual()){
   Serial.println("SENHA OK");
   bip();
  digitalWrite(rele,1);
  delay(2000);
  digitalWrite(rele,0);
  while (igual()){
   delay(100);
  } 
  }
  
  if(!digitalRead(grava)){
    Serial.println("gravando");
    grava_senha();
    bip();
    Serial.println("gravado");
    while(!digitalRead(grava)){delay(100);}
  }
  
  for(int i = 0;i<16;i++){
    Serial.print(digitado[i]); 
  }
  Serial.println();
}

boolean igual(){
  atualiza();
  for(int i = 0;i<16;i++){
     if (digitado[i] != senha[i]){
      return false; 
     }
  }
  return true;
}


void atualiza(){
 for(int i = 0;i<8;i++){
    if(pcf.digRead(i)){
      Serial.print("1 - ");
      Serial.println(i);
      if (!digitado[i]){bip_but(); Serial.println(i);} 
      
      digitado[i] = 1;
    }else{
      digitado[i] = 0;
    }
   if(pcf2.digRead(i)){
      Serial.print("2 - ");
      Serial.println(i);
      if (!digitado[i+8]){bip_but();Serial.println(i);}
     digitado[i+8] = 1;
    }else{
      digitado[i+8] = 0;
    }
  } 
}

void grava_senha(){
 for(int i = 0;i<16;i++){
    EEPROM.write(i+1,digitado[i]);
    senha[i] = digitado[i];
  } 
}

void bip(){
  
tone(buzzer,1599,100);delay(100);tone(buzzer,1299,100);delay(100);
tone(buzzer,1499,100);delay(100);tone(buzzer,1399,100);delay(100);
tone(buzzer,1299,100);delay(100);tone(buzzer,1499,100);delay(1000); 
  
}



void bip_but(){
 tone(buzzer,2000,100);delay(100);tone(buzzer,2500,100); 
}
