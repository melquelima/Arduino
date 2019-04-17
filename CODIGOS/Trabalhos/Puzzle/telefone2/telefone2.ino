#include <EEPROM.h>
#include <pcfXpand.h>
#include <Wire.h> 
#include <mills.h>
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

#define SD_ChipSelectPin 4
#define SPEAKERPIN 9

pcfXpand pcf2(39,INPUT); // endereço do CI a ser lido
pcfXpand pcf(32,INPUT); // endereço do CI a ser lido
mills tempo(2000); // declara o tempo a ser estabelecido

String senha_digitada = "";
String senha1 = lerSenha('*');
String senha2 = lerSenha('#');
int buzzer = A1;
TMRpcm tmrpcm;

void setup() {
  //Serial.begin(9600);
  //tmrpcm.setVolume(5);
  //tmrpcm.quality(1); 
  
  pinMode(buzzer,OUTPUT);
  tmrpcm.speakerPin = SPEAKERPIN;
  
 if(pcf.begin() && pcf2.begin()){
    //Serial.println("PCFS OK");
  }else{
   bip(3);
  }
  
  if (SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    //Serial.println("SD OK");
    bip(1);
  }else{
   //Serial.println("SD fail");   
   bip(4);
   //while(1){}
  }
  
  
  tempo.on();
 
    /*Serial.println("===============================");
    Serial.print("senha1: ");
    Serial.println(senha1);
    Serial.print("senha2: ");
    Serial.println(senha2);
    Serial.println("========== INICIO =============");
  */
}

void loop() {
   char tecla = digitado();
   
     if(tecla == '*' || tecla == '#'){
    tempo.reset();
    while(tecla == '*' || tecla == '#'){
      if(tempo.verifica()){
         //Serial.println("========== CONFIGURACAO DE SENHA =============");
         configuraSenha(tecla);
      }
      tecla = digitado();
    }
  }else if(tecla != ' ' && tecla != '&'){
    senha_digitada += tecla;
    senha_digitada = senha_digitada.length()>9?"":senha_digitada;
    while(digitado() != ' '){delay(200);}
  }
    /*if(tecla != ' ' && tecla != '&'){
     Serial.print("senha_digitada: ");
     Serial.println(senha_digitada);
   }*/
    if(tecla == '&'){
    //Serial.println("========== INICIO =============");
    senha_digitada = "";
   }
   
     if(senha_digitada.length()==9){
    if(senha_digitada == senha1){
      //Serial.println("==========> SENHA CONFERE 1");
      tmrpcm.play("dica1.wav");
      while(tmrpcm.isPlaying()){}
    }else if (senha_digitada == senha2){
      //Serial.println("==========> SENHA CONFERE 2");
      tmrpcm.play("dica2.wav");
      //while(tmrpcm.isPlaying()){}
    }else{
     //Serial.println("==========> SENHA NAO CONFERE"); 
    }
    senha_digitada = "";
    //Serial.println("========== INICIO =============");
  }

   
    if(!tmrpcm.isPlaying() && senha_digitada == ""){
      tmrpcm.play("tuu.wav");
    }
   
}


void configuraSenha(char tipo){
  //Serial.println("Configure uma senha de 8 digitos");
  String senha = "";
  int cont = 0;
  bip(4);
  while(cont < 9){
    char tecla = digitado();
    if(tecla - 48 >= 0 && tecla - 48 <=9){
      cont ++;
      senha += tecla;
      /*Serial.print("Senha: ");
      Serial.print(tecla - 48,DEC);
      Serial.print(" - ");
      Serial.println(senha);*/
      while(digitado() != ' '){delay(200);}
    }
  }
  
  for (int i = 0,pos = (tipo=='*'?8:20);i<senha.length();i++,pos++){
    EEPROM.write(pos,senha[i]);
  }
   bip(4);
  senha1 = lerSenha('*');
  senha2 = lerSenha('#');
  //Serial.println("================== SENHA CONFIGURADA =================");
  //Serial.println("========== INICIO =============");
}


void bip(int vezes){
  for(int i = 0;i<vezes;i++){
    digitalWrite(buzzer,1);
    delay(100);
    digitalWrite(buzzer,0);
    delay(100);
  }
}


char digitado(){
 char retorno =' ';
  char teclas_pcf1[8] = {'0','1','2','3','4','5','6','7'};
  char teclas_pcf2[8] = {'8','9','*','#','&',' ',' ',' '};
    for (int i = 0;i<=7;i++){
      if(pcf.digRead(i)){
         retorno = teclas_pcf1[i];
         tmrpcm.play("tone.wav");
         while(pcf.digRead(i)){delay(200);}
        return retorno;
      }
      if(pcf2.digRead(i)){
        retorno = teclas_pcf2[i];
         tmrpcm.play("tone.wav");
         while((retorno == '*' || retorno == '#')?false:pcf2.digRead(i)){delay(200);}
        return retorno;
      }
    }
    return ' ';
}

String lerSenha(char tipo){
  String senha = "";
  int pos = (tipo=='*'?8:20);
  
  for (int i = 0;i<9;i++){
    senha += (char)EEPROM.read(pos+i);
  }
  
  return senha;
}

