#include "EEPROM.h"
String senha;

void setup(){
  Serial.begin(9600);
  senha = pega_senha();
}
void loop(){
  if(Serial.available()){
    char comando = Serial.read();
    if(comando == 'a'){
      nova_senha();
    }
  }
}
void nova_senha(){
  Serial.println("digite uma nova senha com 4 digitos");
  int new_pass[4];
  int count =0;
  while(count != 4){
    if(Serial.available()){
      int valor = Serial.read();
      if(valor>=48 && valor <=57){
        Serial.print("valor digitado: ");
        Serial.println(valor);
       new_pass[count] = valor; 
        count ++; 
      }
      else{
        Serial.println("valor digitado nao e valido");
      }
    } 
    //Serial.println(sizeof(new_pass)/sizeof(new_pass[0]));
  }
  EEPROM.write(0,new_pass[0]);
  EEPROM.write(1,new_pass[1]);
  EEPROM.write(2,new_pass[2]);
  EEPROM.write(3,new_pass[3]);
  senha = pega_senha();
  Serial.println("Senha cadastrada com sucesso");
}

String pega_senha(){
  char a = EEPROM.read(0);
  char b = EEPROM.read(1);
  char c = EEPROM.read(2);
  char d = EEPROM.read(3);
  String pass = pass + a + b + c + d;
  Serial.println(pass);
  return (pass);
}





