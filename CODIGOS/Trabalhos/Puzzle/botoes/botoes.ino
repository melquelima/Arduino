#include <mills.h>
#include <EEPROM.h>
#include <pcfXpand.h>
#include <Wire.h> 

pcfXpand pcf(39,INPUT); // endereço do CI a ser lido

mills tempo(3000);

int btn_grava = 5;
int pressionados[8];
int compara[8]={9,9,9,9,9,9,9,9};
int leds[8] = {6,7,2,9,10,11,12,13};
int vezes;  
int aux_compara;
int buzzer = 3;
int rele= 4;

void setup() {
  Serial.begin(9600);
   senha_memoria();
   vezes = tamanho();
pinMode(btn_grava,INPUT_PULLUP);
for(int i = 0;i<8;i++)
pinMode(leds[i],OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(rele,OUTPUT);

}

void loop() {
  if(!digitalRead(btn_grava)){
    pega();
  }
  for(int i = 0;i<8;i++)
  if(pcf.digRead(i+1)){
    bip_but();
    tempo.inicio();
    if(!repetido(i)){
    compara[aux_compara] = i;
    aux_compara++;
    digitalWrite(leds[i],1);
    Serial.print("Digitado: ");
    Serial.print(i);
    Serial.print("aux_compara: ");
    Serial.print(aux_compara); 
    Serial.print("vezes: ");
    Serial.println(vezes);  
   }
   while(pcf.digRead(i+1)){}
   delay(200);
 }
 if(aux_compara == vezes){
   Serial.println("Comparado");
   aux_compara = 0;
   if(compativel()){
    Serial.println("Confere");
    bip();
    digitalWrite(rele,1);
    delay(1000);
    digitalWrite(rele,0);
    apaga_leds();
   for(int i = 0;i<8;i++){digitalWrite(leds[i],1);delay(100);}
  for(int i = 0;i<8;i++){digitalWrite(leds[i],0);delay(100);} 
   }else{
    Serial.println("Nao Confere"); 
 bip_rong();  
 }
   apaga_leds();
   for(int i = 0;i<8;i++)
   compara[i] = 9;
   delay(400);
 }else {
    if (tempo.verifica() && aux_compara != 0) {
      bip_rong();
      Serial.println("Senha resetada");
      for (int i = 0; i < 8; i++)
        compara[i] = 9;
      aux_compara = 0;
      apaga_leds();
    }

  }
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

void apaga_leds(){
 for(int i = 0;i<8;i++)
 digitalWrite(leds[i],0); 
}

boolean compativel(){
if((compara[0] == pressionados[0])&&(compara[1] == pressionados[1])&&(compara[2] == pressionados[2])&&(compara[3] == pressionados[3])&&(compara[4] == pressionados[4])&&(compara[5] == pressionados[5])&&(compara[6] == pressionados[6])&&(compara[7] == pressionados[7]))
return true;
return false;
}


void pega(){
  for(int i = 0;i<8;i++)
  pressionados[i]=9;
  
  int pos = 0;
  Serial.println("Digite as posicoes a serem gravadas");
  while(!digitalRead(btn_grava)){
    for(int i = 0;i<8;i++){
     if(pcf.digRead(i+1)){
       bip_but();
       digitalWrite(leds[i],1);
       if(!verifica_duplicado(i)){ //verifica se um botao foi rpessionado mais d euma vez
         pressionados[pos] = i;
         pos++; 
         Serial.print("Posicao ");
         Serial.print(i);
         Serial.println(" gravada");   
       }
       while(pcf.digRead(i+1)){}
       delay(200);
     }
    }
  }
  apaga_leds();
  salva();
  aux_compara = 0;
  Serial.println("gravado");
  Serial.println(tamanho());
  vezes = tamanho();
  for(int i = 0;i<8;i++)
    compara[i] = 9;
}

void senha_memoria(){
    Serial.print("Senha cadastrada: ");
  for(int i = 0;i<8;i++){
   pressionados[i] = EEPROM.read(i);
   Serial.print(pressionados[i]); 
  }  
     Serial.println();
}

int tamanho(){
  int total;
    for(int i = 0;i<8;i++){
      if(pressionados[i]==9){
        delay(500);
       Serial.println(i);
      return i;
      }
      //total = (pressionados[i]==9?total+1:total); 
     //Serial.print(total);
 }
 Serial.println();
 Serial.print("vezes = ");
 Serial.println(8);
 return 8;
}







void salva(){
  for(int i = 0;i<8;i++){
   EEPROM.write(i,pressionados[i]); 
  }
  
}

boolean verifica_duplicado(int valor){ //verifica se um botao foi rpessionado mais d euma vez
   for(int i = 0;i<8;i++){
    if (pressionados[i] == valor){
      Serial.println("duplicado");
     return true;
    } 
   }
   return false; 
}

boolean repetido(int valor){ //verifica se um botao foi rpessionado mais d euma vez
   for(int i = 0;i<8;i++){
    if (compara[i] == valor){
      Serial.print("duplicado - ");
      Serial.print(valor);
      Serial.print(" - ");
       for(int i = 0; i<8;i++){ 
          Serial.print(compara[i]);
         }
          Serial.println();
     return true;
    } 
   }
   return false;
    
}


int tamanho_memoria(){
  int total = 0 ;
    for(int i = 0;i<8;i++){
       if (compara[i] != 9){
      total++;
    } 
 }
 return total;
}
