#include <EEPROM.h>
#include <pcfXpand.h>
#include <Wire.h> 

pcfXpand pcf2(39,INPUT); // endereço do CI a ser lido
pcfXpand pcf(32,INPUT); // endereço do CI a ser lido

int count = 0; //variavel a receber a quantidade degerencgere pulsos
boolean comando = true; // variavel que determina a função a ser executada

char teclas[10] = {
  '1','2','3','4','5','6','7','8','9','0'};
String senha;
String senha2;
String digitado;
int count2=0;
int rele = 3;
int buzzer = A1;
//============= SOM ================

#include <SD.h>
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;


void setup() {
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);

  pinMode(rele,OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  if(pcf.begin() && pcf2.begin()){
    Serial.println("PCFS OK");
    bip();
  }
  
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    //return;   // don't do anything more if not
    bip2();
  }
  else{
    Serial.println("SD OK");
    bip();    
  }

  Serial.println("Digite a senha com 8 numeros");
  pega_senha();
}

void loop() {
  if(pcf2.digRead(2)){
    Serial.println("Digite a senha com 8 numeros");
    count2 = 0;
    digitado = "";
    tmrpcm.play("tone.wav");
    while(pcf2.digRead(2)){
    }
    tmrpcm.play("tuu.wav");
  }
  for (int i = 1;i<=8;i++){
    if(pcf2.digRead(i) && i != 6 && i != 3 && i != 2){
      Serial.print("Pcf2: ");
      Serial.write((i==1?teclas[i+7]:(i==7?teclas[i+2]:i)));
      Serial.println(); 
      tmrpcm.play("tone.wav");
      if(i == 1 || i ==7){
        count2++;
        digitado = digitado + teclas[(i==1?8:9)];
        Serial.println(digitado);
      }
      while(pcf2.digRead(i)){
      }  
    }
    if(pcf.digRead(i)){
      tmrpcm.play("tone.wav");
      Serial.print("Pcf1: ");
      Serial.println(teclas[i-1]);
      count2++;
      digitado = digitado + teclas[i-1];
      Serial.println(digitado);
      while(pcf.digRead(i)){
      } 
    }
  }
  if(count2 == 8){
    if(senha == digitado || senha2 == digitado){
      Serial.println("========SENHA CONFERE========");
      if(senha == digitado){
        tmrpcm.play("dica1.wav");
      }
      else{
        tmrpcm.play("dica2.wav");
      }
      digitalWrite(rele,1);
      delay(1000);
      digitalWrite(rele,0);
      count2= 0;
      digitado = "";  
    }
    else{
      Serial.println("========SENHA NAO CONFERE========"); 
      count2= 0;
      digitado = "";
    }
  }

  for (int i = 3;i<=6;i++){
    if(i== 3 || i ==6)
      if (pcf2.digRead(i)) {  //se o botao for pressionado
        count = 0;                //zera count
        while (pcf2.digRead(i)) { // enquanto o totao estiver pressionado
          count++;             // adciona mais 1 a count
          delay(200);           // espera 200milisegundos
          if (count == 10) {    // verifica se count eigual a 10 se for
            if(i == 6){
              conf_senha1();
            }
            else{
              conf_senha2();
            }
            comando = false;       // indica que a outra função nao sera executada
            while (pcf2.digRead(i)) {
            } // espera o usuario tirar o dedo do botao
          }
        }
      }
  }


}

void conf_senha2(){
  Serial.println("2: Configure uma senha de 8 digitos");
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  int quant = 0;
  int senhaInt[8];

  while(quant != 8){
    for (int i = 1;i<=8;i++){
      if(pcf2.digRead(i) && i != 6 && i != 3 && i != 2){
        tmrpcm.play("tone.wav");
        Serial.print("Pcf2: ");
        Serial.write((i==1?teclas[i+7]:(i==7?teclas[i+2]:i)));
        Serial.println(); 
        quant++;
        senhaInt[quant-1]= (i==1?9:0);
        while(pcf2.digRead(i)){
        }  
      }
      if(pcf.digRead(i)){
        tmrpcm.play("tone.wav");
        Serial.print("Pcf1: ");
        Serial.println(teclas[i-1]);
        quant++;
        senhaInt[quant-1] = i;
        while(pcf.digRead(i)){
        } 
      }
    }
  }
  for(int i =8; i<=15;i++){
    EEPROM.write(i,senhaInt[i-8]);
  }
  pega_senha();
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);

}




void conf_senha1(){
  Serial.println("1: Configure uma senha de 8 digitos");
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  int quant = 0;
  int senhaInt[8];

  while(quant != 8){
    for (int i = 1;i<=8;i++){
      if(pcf2.digRead(i) && i != 6 && i != 3 && i != 2){
        tmrpcm.play("tone.wav");
        Serial.print("Pcf2: ");
        Serial.write((i==1?teclas[i+7]:(i==7?teclas[i+2]:i)));
        Serial.println(); 
        quant++;
        senhaInt[quant-1]= (i==1?9:0);
        while(pcf2.digRead(i)){
        }  
      }
      if(pcf.digRead(i)){
        tmrpcm.play("tone.wav");
        Serial.print("Pcf1: ");
        Serial.println(teclas[i-1]);
        quant++;
        senhaInt[quant-1] = i;
        while(pcf.digRead(i)){
        } 
      }
    }
  }
  for(int i =0; i<=7;i++){
    EEPROM.write(i,senhaInt[i]);
  }
  pega_senha();
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
}

void pega_senha(){
  senha ="";
  senha2 = "";
  for (int i = 0; i<=7;i++){
    if(EEPROM.read(i) != 0 && EEPROM.read(i) != 9 ){
      senha = senha + teclas[EEPROM.read(i)-1];
    }
    else{
      senha = senha + teclas[(EEPROM.read(i)==0?9:8)];
    }
  }

  for (int i = 8; i<=15;i++){
    if(EEPROM.read(i) != 0 && EEPROM.read(i) != 9 ){
      senha2 = senha2 + teclas[EEPROM.read(i)-1];
    }
    else{
      senha2 = senha2 + teclas[(EEPROM.read(i)==0?9:8)];
    }
  }

  Serial.println("Senha 1: " + senha);
  Serial.println("Senha 2: " + senha2);
}

void bip(){
 
  digitalWrite(buzzer,1);
    delay(100);
  digitalWrite(buzzer,0);
    delay(100);
  digitalWrite(buzzer,1);
    delay(100);
  digitalWrite(buzzer,0);
    delay(100);
  digitalWrite(buzzer,1);
    delay(100);
  digitalWrite(buzzer,0);
    delay(100);
  
}


void bip2(){
 
  digitalWrite(buzzer,1);
    delay(100);
  digitalWrite(buzzer,0);
}
