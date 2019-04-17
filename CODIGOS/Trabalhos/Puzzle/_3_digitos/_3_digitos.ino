#include <TimerOne.h>
#include <EEPROM.h>

int _A = 2;
int _B = 3;
int _C = 4;

int seg[7] = {
  11,12,A1,A0,13,10,9};
int numero[3] = {
  0,0,0};
int senha[3] = {
  EEPROM.read(1),EEPROM.read(2),EEPROM.read(3)};
int atual = 1;
int pot1 = A2;
int pot2 = A3;
int pot3 = A4;
int but = 0;
int rele  = 1;

boolean mostra = true;
boolean inicia = false;
int range[10][2]={
  {
    0,40    }
  ,{
    62,142    }
  ,{
    164,244    }
  ,{
    266,346    }
  ,{
    328,448    }
  ,{
    470,550    }
  ,{
    572,652    }
  ,{
    674,754    }
  ,{
    776,856    }
  ,{
    878,958    }
};

void setup(){
  Serial.end();
  pinMode(_A,OUTPUT);
  pinMode(_B,OUTPUT);
  pinMode(_C,OUTPUT);
  pinMode(rele,OUTPUT);
  pinMode(but,INPUT_PULLUP);

  for(int i = 0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }

  Timer1.initialize(5000);
  Timer1.attachInterrupt( _display );

  numero[0] = senha[0];
  numero[1] = senha[1];
  numero[2] = senha[2];
  pisca();
  numero[0] = 0;
  numero[1] = 0;
  numero[2] = 0;
  inicia = true;
}

void loop(){

  if(senha[0] == numero[0] && senha[1] == numero[1] && senha[2] == numero[2]){
    digitalWrite(rele,1);
    delay(2000);
    digitalWrite(rele,0);
    pisca();
    while(senha[0] == numero[0] && senha[1] == numero[1] && senha[2] == numero[2]){
    delay(1);
    }
  }

  if (!digitalRead(but)){
    EEPROM.write(1,numero[0]);
    EEPROM.write(2,numero[1]);
    EEPROM.write(3,numero[2]);
    senha[0] = numero[0];
    senha[1] = numero[1];
    senha[2] = numero[2];
    pisca();
    
    while(!digitalRead(but)){
    }
    delay(300);
  }

}

void pisca(){
  mostra = false;
  delay(500);
  mostra = true;
  delay(500);
  mostra = false;
  delay(500);
  mostra = true;
  delay(500);
  mostra = false;
  delay(500);
  mostra = true;

}

void _display(){

  if (inicia){
    int valor1 = analogRead(pot1);
    int valor2 = analogRead(pot2);
    int valor3 = analogRead(pot3);

    for(int j=0;j<10;j++){
      numero[0] = valor1>=range[j][0] && valor1<=range[j][1]?j:numero[0];
      numero[1] = valor2>=range[j][0] && valor2<=range[j][1]?j:numero[1];
      numero[2] = valor3>=range[j][0] && valor3<=range[j][1]?j:numero[2];
    }
  }  


  if (mostra){
    switch (atual){
    case 1:
      numeros(_A,numero[0]);
      break;
    case 2:
      numeros(_B,numero[1]);
      break;
    case 3:
      numeros(_C,numero[2]);
      break; 
    }
    atual++;
    atual = atual==4?1:atual;
  }
  else{
    apaga();
  }

}


void numeros(int porta, int numero){
  apaga();
  digitalWrite(_A,0);
  digitalWrite(_B,0);
  digitalWrite(_C,0);
  digitalWrite(porta,1);

  switch (numero){
  case 0:
    for(int i = 0;i<6;i++){
      digitalWrite(seg[i],0);
    } 
    break;
  case 1:
    digitalWrite(seg[1],0);
    digitalWrite(seg[2],0);
    break;
  case 2:
    digitalWrite(seg[0],0);
    digitalWrite(seg[1],0);
    digitalWrite(seg[3],0);
    digitalWrite(seg[4],0);
    digitalWrite(seg[6],0);
    break;
  case 3:
    digitalWrite(seg[0],0);
    digitalWrite(seg[1],0);
    digitalWrite(seg[2],0);
    digitalWrite(seg[3],0);
    digitalWrite(seg[6],0);
    break;
  case 4:
    digitalWrite(seg[1],0);
    digitalWrite(seg[2],0);
    digitalWrite(seg[6],0);
    digitalWrite(seg[5],0);
    break;
  case 5:
    digitalWrite(seg[0],0);
    digitalWrite(seg[2],0);
    digitalWrite(seg[5],0);
    digitalWrite(seg[6],0);
    digitalWrite(seg[3],0);
    break;
  case 6:
    digitalWrite(seg[0],0);
    digitalWrite(seg[2],0);
    digitalWrite(seg[3],0);
    digitalWrite(seg[4],0);
    digitalWrite(seg[5],0);
    digitalWrite(seg[6],0);
    break;
  case 7:
    digitalWrite(seg[0],0);
    digitalWrite(seg[1],0);
    digitalWrite(seg[2],0);
    break;
  case 8:
    for(int i = 0;i<7;i++){
      digitalWrite(seg[i],0);
    }
    break;
  case 9:
    digitalWrite(seg[0],0);
    digitalWrite(seg[1],0);
    digitalWrite(seg[2],0);
    digitalWrite(seg[5],0);
    digitalWrite(seg[6],0);
    break;
  } 
}


void apaga(){
  for(int i = 0;i<7;i++){
    digitalWrite(seg[i],1);
  } 
}






