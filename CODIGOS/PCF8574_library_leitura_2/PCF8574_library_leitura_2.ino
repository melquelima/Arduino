#include <Wire.h>

int adress[2] ={32,39};

byte x = 0;

void setup() {
Wire.begin();
Serial.begin(9600);

}

void loop() {
 int botao = digRead();
 if(botao != 0){
   Serial.println(botao); 
   delay(200);
 }
  
}

int digRead(){ // retorna de 1 a 8 referente ao botao pressionado

for(int k=0; k<=1;k++){
 Wire.requestFrom(adress[k],1);  // pergunta se algum botao foi pressionado
  if(Wire.available())     //se sim...
  {
    x = Wire.read(); // recebe o valor do botao

    for (int j = 0; j <= 7; j++){
      if (!(x & (1 << j))) {return (k==0?j+1:j+9);} 
    } 
   
  }
  
}
   return 0; 
}




