#include <Wire.h>

int adress = 32;
byte x = 0;

void setup() {
Wire.begin();
Serial.begin(9600);

}

void loop() {
 int botao = digRead();
   Serial.println(botao); 
   delay(500);
  
}

int digRead(){ // retorna de 1 a 8 referente ao botao pressionado
 Wire.requestFrom(adress,1);  // pergunta se algum botao foi pressionado
  if(Wire.available())     //se sim...
  {
    x = Wire.read(); // recebe o valor do botao

    for (int j = 0; j <= 7; j++){
      if (!(x & (1 << j))) {return j+1;} 
    } 
    
  }
   return 9; 
}





/*
  switch (x){
   case 254:
    return 1;
   break;
   case 253:
    return 2;
   break;
   case 251:
   return 3;
   break;
   case 247:
  return 4;
   break;
   case 239:
  return 5;
   break;
   case 223:
  return 6;
   break;
   case 191:
  return 7;
   break;
   case 127:
  return 8;
   break;   
  }
   
  
}


*/

