#include <mills.h>
#include "EEPROM.h"
mills tempo(1000);

int botao = 12;
int rele = 11;
int batidas = ler();
int compara = 0;
int reseta = false;

void setup() {
  Serial.begin(9600);
  pinMode(botao, INPUT_PULLUP);
  pinMode(rele, OUTPUT);

}

void loop() {
  if (!digitalRead(botao)) {
    grava();
    delay(100);
  }
  if (piezo()) {
    compara ++;
    delay(70);
    tempo.inicio();
    reseta = true;
  }

  if (tempo.verifica()&& reseta) {
    if (compara == batidas) {
      Serial.println("OK");
      digitalWrite(rele, 1);
      delay(1000);
      digitalWrite(rele, 0);
    }else{
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
  Serial.println("====CONFGURACAO INICIADA====");
  batidas = 0;
  while (!digitalRead(botao)) {
    if (piezo()) {
      batidas ++;
      delay(70);
    }
  }
  Serial.print("==== GRAVADO >>");
  Serial.println(batidas);
  EEPROM.write(1, batidas);
  delay(100);
}

int ler() {
  return EEPROM.read(1);
}

boolean piezo(){
  int leitura = analogRead(0);
  if (leitura > 200){
   while(leitura>50){
    leitura = analogRead(0);
   }
  return true; 
  }
  return false;
}



