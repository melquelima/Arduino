#include <EEPROM.h>

int digitado[10];
int senha[10]={0,1,2,3};
int N_digitos = 4;
int botoes[4] ={6,7,8,9};
int leds[4] ={3,5,2,4}; 

int menu = 10;
int n = 0;
int tempo = 4000;
int rele = 11;
unsigned long int anterior=0;

void setup() {
  if (EEPROM.read(1) >10) {
    EEPROM.write(1,4);
    EEPROM.write(2,0);
    EEPROM.write(3,1);
    EEPROM.write(4,2);
    EEPROM.write(5,3);
  }
  Serial.begin(9600);
  delay(100);
  Serial.println("inicio");
  for (int i = 0;i<4;i++){
    pinMode(botoes[i],INPUT_PULLUP);
    pinMode(leds[i],OUTPUT); 
  }
  pinMode(rele,OUTPUT);
  pinMode(menu,INPUT_PULLUP);
  eeprom_read();
}

void loop() {
  for (int i = 0;i<4;i++){
    if(!digitalRead(botoes[i])){
      digitalWrite(leds[i],1);
      anterior = millis();
      digitado[n] = i;
      n++;
      Serial.println(i);
      while(!digitalRead(botoes[i])){
        delay(50);
      }
      delay(5);
      while(!digitalRead(botoes[i])){
        delay(50);
      }
      delay(100);
      digitalWrite(leds[i],0); 
    }
  }

  if (n == N_digitos){
    n = 0;
    if(igual()){
      Serial.println("SENHA CONFERE");
      senha_ok();
      digitalWrite(rele,1);
      delay(10000);
      digitalWrite(rele,0);
    }
    else{
      Serial.println("SENHA NAO CONFERE");
      senha_Nok();
    }
    limpa_digitos();
    delay(500);
  }

  if (n != 0 && millis()-anterior >= tempo){
    Serial.println("RESETADO");
    senha_Nok();
    n= 0;
    limpa_digitos();
  }

  if (!digitalRead(menu)){
    Serial.println("MENU");
    menu_led();
    while(!digitalRead(menu)){
      delay(50);
    }
    delay(100);
    n= 0;
    limpa_digitos();

    int nova[10];
    int digitos=0;

    while(digitalRead(menu)){
      for (int i = 0;i<4;i++){
        if(!digitalRead(botoes[i])){
          digitalWrite(leds[i],1);
          nova[digitos] = i;
          digitos++;
          Serial.println(i);
          while(!digitalRead(botoes[i])){
            delay(50);
          }
          delay(5);
          while(!digitalRead(botoes[i])){
            delay(50);
          }
          delay(100);
          digitalWrite(leds[i],0); 
        }
      }
    }
    N_digitos = digitos;
    Serial.println("SAIU MENU");
    for(int h = 0;h<digitos;h++){
      Serial.print(nova[h]);
      senha[h]= nova[h]; 
    }
    Serial.println();
    eeprom_wrire();
    menu_led();
    while(!digitalRead(menu)){
      delay(50);
    }
    delay(400);

  }


}

void limpa_digitos(){
  for (int i = 0;i<N_digitos;i++){
    digitado[i] = 99;
  }
}

boolean igual(){
  for (int i = 0;i<N_digitos;i++){
    if (digitado[i] != senha[i]){
      return false;
    } 
  }
  return true;
}

void ler_EEPROM(){
  limpa_digitos();

}


void senha_ok(){
  int leds2[4]= {
    leds[0],leds[1],leds[3],leds[2],  };
  int tempo = 100;
  for (int j = 0;j<3;j++){
    for (int i = 0;i<4;i++){
      digitalWrite(leds2[i],1);
      delay(tempo);
    }
    for (int i = 0;i<4;i++){
      digitalWrite(leds2[i],0);
      delay(tempo);
    }
  }
}


void senha_Nok(){
  int tempo = 100;
  for (int j = 0;j<2;j++){
    for (int i = 0;i<4;i++){
      digitalWrite(leds[i],1);
    }
    delay(200);
    for (int i = 0;i<4;i++){
      digitalWrite(leds[i],0);
    }
    delay(200);
  }
}

void menu_led(){
  int tempo = 50;
  for (int j = 0;j<20;j++){
    for (int i = 0;i<4;i++){
      digitalWrite(leds[i],1);
    }
    delay(tempo);
    for (int i = 0;i<4;i++){
      digitalWrite(leds[i],0);
    }
    delay(tempo);
  }
}

void eeprom_read(){
  N_digitos = EEPROM.read(1);
  Serial.println(N_digitos);

  for (int k = 0;k<N_digitos;k++){
    senha[k] = EEPROM.read(k+2);
    Serial.print(senha[k]);
  }
  Serial.println();
}

void eeprom_wrire(){
  EEPROM.write(1,N_digitos);

  for (int i = 0;i<N_digitos;i++){
    EEPROM.write(i+2,senha[i]);
  }
}


