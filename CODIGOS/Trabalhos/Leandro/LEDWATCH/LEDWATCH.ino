#include <mills.h>
#define NUMT 9
#define NUML 6

mills tempo(5000);

int rele = 13;
int TERMINAIS [NUMT] = {2,3,4,5,6,7,8,9,10};
int LEDS [NUML] = {A0,A1,A2,A3,A4,A5};
String Senha[6]={"12","13","14","15","16","17"};
boolean acertos[6]={false,false,false,false,false,false};

void setup() {
  Serial.begin(9600);
  for(int i =0;i<NUML;i++){
    pinMode(LEDS[i], OUTPUT);
    } 
    pinMode(rele,OUTPUT);
    digitalWrite(rele,1);
     
}

void loop() {
  String pres = Pressionado();
  
  if(pres != ""){
    tempo.on();
    tempo.reset();
    contem(pres);
    Serial.println(pres);
    pres = "";
  }
  
   if(tempo.verifica()){
     tempo.off();
     zeraTudo(); 
   }
   
   if(!existe(false)){
    zeraTudo();
    digitalWrite(rele,0);
    pisca();
    delay(2000);
    digitalWrite(rele,1);
   }
   
}

boolean existe(boolean x){
  for(int t=0;t<NUML;t++){
     if(acertos[t] == x){
       return true;
     }
   }
   return false;
}

void contem(String valor){
  String valor2 = String(valor[1]) + String(valor[0]);
   for(int t=0;t<NUML;t++){
     if(Senha[t] == valor || Senha[t] == valor2){
       acertos[t] = true;
       digitalWrite(LEDS[t],HIGH);
       return;
     }
   }
 zeraTudo();
}

void zeraTudo(){
    for(int t=0;t<NUML;t++){
     acertos[t] = false;
     digitalWrite(LEDS[t],LOW);
   } 
}

  String Pressionado(){
    for(int t=0;t<NUMT;t++){
      ENTRADA();
      pinMode(TERMINAIS[t], OUTPUT);
      digitalWrite(TERMINAIS[t], LOW);
      for(int l =0;l<NUMT;l++){
      if(t != l && !digitalRead(TERMINAIS[l])) {
        //while(!digitalRead(TERMINAIS[l])){delay(200);}
          return String(t) + String(l);
        }
      }
    }

  return "";
  }

  void ENTRADA(){
    for(int i=0;i<NUMT;i++){
      pinMode(TERMINAIS[i], INPUT_PULLUP);
   }
}

void pisca(){
 for(int j=0;j<10;j++){ 
  for(int i=0;i<NUMT;i++){
     digitalWrite(LEDS[i],HIGH);
     if(i>0){
       digitalWrite(LEDS[i-1],LOW);
     }
     delay(100);
  }
 }
}
    
