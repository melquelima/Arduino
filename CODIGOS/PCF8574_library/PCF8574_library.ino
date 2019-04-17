#include <Wire.h>
int adress = 32;
byte numero[8] = {0,0,0,0,0,0,0,0};


void setup() {
   Wire.begin();
   Wire.beginTransmission(adress);
   Wire.write(B0000000);
   Wire.endTransmission();

}

void loop() {
  
  digWrite(5,1);
  delay(400);
  digWrite(5,0);
  delay(400);
  
 }
 
 void digWrite(int pt, int valor){
  
    numero[pt-1] = valor;
    int num =
    (numero[7]*1) + 
    (numero[6]*2) + 
    (numero[5]*4) + 
    (numero[4]*8) + 
    (numero[3]*16) + 
    (numero[2]*32) + 
    (numero[1]*64) + 
    (numero[0]*128);

  Wire.beginTransmission(adress);
  Wire.write(num);
  Wire.endTransmission();   
 }
