#include <SPI.h>
#include <nRF24L01p.h>
#include <pcfXpand.h>
#include <Wire.h> 

//--------------------------------PINAGEM
#define AN_ESQ_B_PIN 2
#define AN_ESQ_X_PIN A6
#define AN_ESQ_Y_PIN A7

#define AN_DIR_B_PIN 3
#define AN_DIR_X_PIN A0
#define AN_DIR_Y_PIN A1

//------------------------------- ORDEM

#define PCF1_STATUS 0
#define PCF2_STATUS 1
#define START 2
#define SELECT 3
#define HOTKEY 4
#define AN_ESQ_B 5
#define AN_ESQ_X 6
#define AN_ESQ_Y 7
#define AN_DIR_B 8
#define AN_DIR_X 9
#define AN_DIR_Y 10
#define L1 11
#define L2 12
#define R1 13
#define R2 14
#define ESQ 15
#define DIR 16
#define CIM 17
#define BAIXO 18
#define CHIS 19
#define oo 20
#define AA 21
#define DD 22


nRF24L01p transmitter(8,7);//CSN,CE
pcfXpand pcf(56,0); // endereço do CI a ser lido
pcfXpand pcf2(63,0); // endereço do CI a ser lido

// PCF1_STATUS | PCF2_STATUS | START | SELECT | HOTKEY | AN_ESQ_B | AN_ESQ_X | AN_ESQ_Y | AN_DIR_B | AN_DIR_X | AN_DIR_Y | L1 | L2 | R1 | R2 | ESQ | DIR | CIM | BAIXO
byte buffer[24] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte leds[4] = {5,6,9,10};

void setup(){
  delay(150);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  pinMode(3,INPUT_PULLUP);
  
  for(int i=0;i<4;i++)
    pinMode(leds[i],OUTPUT);
    
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();

    if(!pcf.begin()){
     buffer[0] = 0;
  }
   if(!pcf2.begin()){
     buffer[1] = 0;
  }
  digitalWrite(5,0);
  digitalWrite(6,1);
  digitalWrite(9,1);
  digitalWrite(10,0);
}


void loop(){
 buffer[AN_ESQ_X] = analogRead(AN_ESQ_X_PIN);
 buffer[AN_ESQ_Y] = analogRead(AN_ESQ_Y_PIN);
 buffer[AN_DIR_X] = analogRead(AN_DIR_X_PIN);
 buffer[AN_DIR_Y] = analogRead(AN_DIR_Y_PIN);
 buffer[AN_ESQ_B] = !pcf.digRead(AN_ESQ_B_PIN);
 buffer[AN_DIR_B] = !pcf.digRead(AN_DIR_B_PIN);
 
 buffer[HOTKEY] = !pcf2.digRead(0);
  buffer[CIM] = !pcf2.digRead(7);
  buffer[DIR] = !pcf2.digRead(6);
  buffer[ESQ] = !pcf2.digRead(5);
  buffer[BAIXO] = !pcf2.digRead(4);
   buffer[START] = !pcf2.digRead(3);
   //buffer[SELECT] = !pcf2.digRead(2);
      buffer[DD] = !pcf2.digRead(1);
      
      buffer[CHIS] = !pcf.digRead(0);
      buffer[AA] = !pcf.digRead(1);
      buffer[oo] = !pcf.digRead(7);
      
      buffer[L1] = !pcf2.digRead(2);
      buffer[L2] = !pcf.digRead(6);
      buffer[R1] = !pcf.digRead(4);
      buffer[R2] = !pcf.digRead(5);
      buffer[23] = !digitalRead(3);

  
      Serial.print("ENVIANDO... ");
      transmitter.txPL(buffer,24);
      transmitter.send(FAST);
      Serial.println("/ ENVIADO");

}
