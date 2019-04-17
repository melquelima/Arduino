#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
int buzzer = 13;
int range_subida = 4; //sensibilidade em metros
float referencia;
int botao = 12;

void setup() {
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(botao,INPUT_PULLUP);
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
        //1 bip para erro
	while (1) {}
  }
  Serial.println("ok");
//2 bips para iniciado
referencia = altura();

      Serial.print("referencia : ");
      Serial.println(referencia);
}
  
void loop() {
  verifica();
  if(!digitalRead(botao)) menu();
//    Serial.print("Altitude = ");
 //   Serial.print(altura());
  //  Serial.println(" meters");
}

void menu(){
  range_subida = (range_subida == 4?6:(range_subida==6?8:10));
digitalWrite(4,0);
digitalWrite(6,0);
digitalWrite(8,0);
digitalWrite(10,0);
digitalWrite(range_subida,1);
while(!digitalRead(botao)){}
delay(200);
}
boolean verifica(){
  for (int i = 1; i<=10;i++){
    float atual = altura();
    if(atual>=referencia+range_subida){
      referencia = atual;
      Serial.print("subindo: ");
      Serial.println(referencia);
      return true;
    }
  }
  for (int i = 1; i<=10;i++){
    float atual = altura();
    if(atual<=referencia-range_subida){
      referencia = atual;
      Serial.print("Descendo : ");
      Serial.println(referencia);
    }
  }
  return false;
}

float altura(){
  float soma = 0;
  for (int i = 1; i<=5;i++){
    soma = soma + bmp.readAltitude();
   delay(2); 
  }
  return soma/5;
}
