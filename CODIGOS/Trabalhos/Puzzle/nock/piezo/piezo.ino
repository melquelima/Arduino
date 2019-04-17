#include <mills.h>
#include "EEPROM.h"
mills tempo(2000);

int botao = 10;
int rele = 11;
int batidas = ler();
int compara = 0;
int reseta = false;
int mais = 3;
int menos = 4;
int coeficiente = EEPROM.read(2);
int buzzer = 9;
int led_piezo = 2;

void setup() {
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  pinMode(botao, INPUT_PULLUP);
  pinMode(mais, INPUT_PULLUP);
  pinMode(menos, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  pinMode(led_piezo, OUTPUT);
  
  digitalWrite(rele, 1);

  if(!digitalRead(mais) && !digitalRead(menos)){
    congifcoef();
  }
  if (!digitalRead(mais)){coef(200); bip();bip();}

  Serial.print("COEF = >");
  Serial.println(coeficiente);
  Serial.println("PROGRAMA INICIADO");
  tempo.on();
}

void coef(int x){
  EEPROM.write(2,x);
  coeficiente = x;
  Serial.print("COEF = >");
  Serial.println(x);
}

void congifcoef(){
      bip();
    int cof = coeficiente;
    Serial.println("CONFIGURACAO DE COEFICIENTE");
  delay(2000);
      while(digitalRead(mais) || digitalRead(menos)){
        if(!digitalRead(mais)){
          cof = cof+10;
          bip_but();
          coeficiente = cof;
          Serial.print("COF  ==>");
          Serial.println(cof);
          while(!digitalRead(mais) && digitalRead(menos));
          delay(200); 
        }
        if(!digitalRead(menos)){
          bip_but();
          cof= cof-10;
          coeficiente = cof;
          Serial.print("COF  ==>");
          Serial.println(cof);
          while(!digitalRead(menos) && digitalRead(mais));
          delay(200); 
        }
        Serial.println(piezo());

    }
    coef(cof);
    Serial.println("CONFIGURACAO DE COEFICIENTE CONCLUIDA");
    bip();
    delay(2000);
    
   
 }

void loop() {

  if (!digitalRead(mais) && !digitalRead(menos)) {
    grava();
  }
  if (piezo()) {
    compara ++;
    delay(70);
    tempo.reset();
    reseta = true;
  }

  if (tempo.verifica()&& reseta) {
    if (compara == batidas) {
      bip();
      Serial.println("OK");
      digitalWrite(rele, 0);
      delay(1000);
      digitalWrite(rele, 1);
    }
    else{
      bip_rong();
      Serial.print("ERROR == ");
      Serial.print(compara);
      Serial.print(" != ");
      Serial.println(batidas);
    }
    compara = 0;
    reseta = false;
  }


}

void grava() {
   bip();
  delay(2000);
  Serial.println("====CONFGURACAO INICIADA====");
  batidas = 0;
  while (digitalRead(mais) || digitalRead(menos)) {
    if (piezo()) {
      batidas ++;
      delay(70);
    }
  }
  Serial.print("==== GRAVADO >>");
  Serial.println(batidas);
  EEPROM.write(1, batidas);
  bip();
  delay(2000);
}

int ler() {
  return EEPROM.read(1);
}

boolean piezo(){
  int leitura = analogRead(0);
  if (leitura > coeficiente){
    while(leitura>coeficiente){
      leitura = analogRead(0);
    }
    bip_but();
    digitalWrite(led_piezo,1);
    delay(20);
    digitalWrite(led_piezo,0);
    return true; 
  }
  return false;
}



void bip_but(){
 tone(buzzer,2000,100);delay(100);tone(buzzer,2500,100); 
}

void bip_rong(){
int tempo = 500;
  tone(buzzer,8000,400);delay(tempo);tone(buzzer,8000,400);
}


void bip(){
  
tone(buzzer,1599,100);delay(100);tone(buzzer,1299,100);delay(100);
 tone(buzzer,1499,100);delay(100);tone(buzzer,1399,100);delay(100);
tone(buzzer,1299,100);delay(100);tone(buzzer,1499,100);delay(1000); 
  
}


