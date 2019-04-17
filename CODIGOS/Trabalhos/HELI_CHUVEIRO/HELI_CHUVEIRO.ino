#include <mills.h>
int Amarelo = 13;
int verde = 12;
int vermelho = 11;
int ONOFF = 10;
int solenoide = 8;
int inicia = false;
mills tempo10(600000); // 10 minutos
mills tempo8(480000); // 8 minutos


void setup() {
  pinMode(Amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(ONOFF, INPUT_PULLUP);
  pinMode(solenoide, OUTPUT);

}

void loop() {
  if (!digitalRead(ONOFF)) {
    while (!digitalRead(ONOFF)) {}
    tempo10.inicio();
    tempo8.inicio();
    inicia = true;
    digitalWrite(solenoide, 1);
    digitalWrite(verde, 1);
  }

  if (tempo10.verifica() && inicia) { // verifica se passou 1 segundo apos o inicio da contagem;
    inicia = false;
    digitalWrite(solenoide, 0);
    digitalWrite(Amarelo, 1);
    espera();
  }

  if (digitalRead(solenoide) && !digitalRead(ONOFF)) {
    inicia = false;
    digitalWrite(solenoide, 0);
    digitalWrite(vermelho, 1);
    espera();
  }

  if (tempo8.verifica() && inicia) { // verifica se passou 1 segundo apos o inicio da contagem;
    inicia = false;
    digitalWrite(Amarelo, 1);
    espera();
  }

}
void espera() {
  delay(300000);// espera 5 minutos
digitalWrite(Amarelo, 0);
digitalWrite(verde, 0);
digitalWrite(vermelho, 0);
}
