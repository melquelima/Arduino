#include <pcfXpand.h>
#include <Wire.h> 
#include <EEPROM.h>

pcfXpand pcf(38,INPUT); // endereço do CI a ser lido
pcfXpand pcf2(39,INPUT); // endereço do CI a ser lido

byte senha[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte senha2[16]={1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1};
//byte senha2[16]={1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0};
int trocasenha = 5;
int rele1 = 13;
int rele2 = 10;

void setup() {
Serial.begin(9600);
pinMode(trocasenha,INPUT_PULLUP);
pinMode(rele1,OUTPUT);
pinMode(rele2,OUTPUT);
readSenha();
}

void loop() {
//Serial.println(pcf2.digRead(8));
//print_array();
troca();
compara();
delay(50); 
}
void troca(){
 if(!digitalRead(trocasenha)){
   for(int i = 0; i<16;i++){
    EEPROM.write(i+1,ler()[i]); 
   }
   readSenha();
  Serial.println("SENHA ALTERADA");
 while(!digitalRead(trocasenha));
 delay(1000);
 }  
}

void compara(){
  boolean valida = true;
  for(int i = 0; i<16;i++){
   if(ler()[i] != senha[i]){
    valida = false;
    exit;
   }
  }
  if(valida){
  Serial.println("OK");
  digitalWrite(rele1,1);
  return;  
  }
  
 valida = true;
  for(int i = 0; i<16;i++){
   if(ler()[i] != senha2[i]){
    valida = false;
    exit;
   }
  }
  if(valida){
  Serial.println("OK2");
digitalWrite(rele2,1);  
return;
}
digitalWrite(rele1,0);
digitalWrite(rele2,0);
}

void readSenha(){
  for(int i = 0; i<=15;i++){
    //EEPROM.write(i+1,0);
   senha[i] = EEPROM.read(i+1);
  }
}

void print_array(){
  
  for(int i = 0; i<16;i++){
   Serial.print(ler()[i]);
   Serial.print(","); 
  }
  Serial.println();
}

boolean* ler(){
  boolean leitura[16];
 
  for(int i = 0; i<8;i++){
    leitura[i] =pcf.digRead(i+1);
  }
  for(int i = 8; i<16;i++){
    leitura[i] =pcf2.digRead(i-7);
  }
  /*
  for(int i = 0; i<16;i++){
    leitura[i] =(i<8?pcf.digRead(i+1):pcf2.digRead(i-7));
  }
  */
  return leitura;
}
