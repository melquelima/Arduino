#include "RunningMedian.h"
#include <mills.h>

mills tempo(100); // declara o tempo a ser estabelecido

RunningMedian samples = RunningMedian(20);
int esquerda, direita;
int range = 4;
int pistola = 13;
int in_esquerda = 4;
// esquerda A0
// direita A1

void setup() {
  pinMode(pistola,OUTPUT);
  Serial.begin(9600);
  configura();
  tempo.inicio();
}
int ativa = 0;
int desativa = 0;

void loop() {
  //    Serial.println(leitura(0));
  ativa = 0;
  desativa = 0;

  while(0){ // enable_esq
    if(esquerda_in()){
      ativa++;
      if(ativa > 40){
        digitalWrite(pistola,1);// ativa pistola
        Serial.println("pistola ativada_esquerda");
        desativa = 0;
      }
    }
    else{
        desativa++;
        if(desativa>60){
          Serial.println("pistola desativada_esquerda");
          digitalWrite(pistola,0);//desativa pistola
          ativa = 0;          
          boolean retorno = false;
          
          while (!retorno){
            Serial.println("aguardando");
           if(!direita_in()){
            ativa++;
            if(ativa>40){
            retorno = true;
            }
           }else{
            ativa = 0;
           } 
          }
          ativa = 0;
          retorno = false;
          
          while (!retorno){
            Serial.println("esperando");
           if(direita_in()){
             ativa++;
             if(ativa >40){
               retorno = true;
             }
           }else{
            ativa = 0;
           } 
          }
          
        digitalWrite(pistola,1);// ativa pistola
        Serial.println("pistola ativada_esquerda");
        }
        ativa = 0;
    }
  }

  ativa = 0;
  desativa = 0;
  
  while(1){ // enable_dir
    if(direita_in()){
      ativa++;
      if(ativa > 40){
        digitalWrite(pistola,1);// ativa pistola
        Serial.println("pistola ativada_direita");
        desativa = 0;
      }
    }
    else{
        desativa++;
        if(desativa>40){
          Serial.println("pistola desativada_direita");
          digitalWrite(pistola,0);//desativa pistola
          ativa = 0;          
          boolean retorno = false;
          
          while (!retorno){
            Serial.println("aguardando");
           if(!esquerda_in()){
            ativa++;
            if(ativa>40){
            retorno = true;
            }
           }else{
            ativa = 0;
           } 
          }
          ativa = 0;
          retorno = false;
          
          while (!retorno){
            Serial.println("esperando");
           Serial.println(ativa);
           if(esquerda_in()){
             ativa++;
             Serial.println(ativa);
             if(ativa >10){
               retorno = true;
             }
           }
          }
          
        digitalWrite(pistola,1);// ativa pistola
        Serial.println("pistola ativada_direita");
        }
        ativa = 0;
    }
  }


}

boolean esquerda_in(){
  if(!(leitura(0)<=esquerda-range || leitura(0)>=esquerda+range)){
    return true;
  }
  return false;  
}

boolean direita_in(){
  if(!(leitura(1)<=direita-(range+1) || leitura(1)>=direita+(range+1))){
    return true;
  }
  return false;  
}


void configura(){
  esquerda = leitura(0);
  direita = leitura(1);
  Serial.print("<---- ");
  Serial.println(esquerda);
  Serial.print("---->");
  Serial.println(direita);
  delay(2000);
}

int leitura(int x){
  int val;
  for(int i = 1; i <= 20;i++){
    samples.add((x==0?analogRead(A0):analogRead(A1)));
  }  
  val =(6762/(samples.getMedian()-9))-4;
  samples.clear();
  return val;
}



