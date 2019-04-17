#include <SPI.h>
#include <nRF24L01p.h>
#include <Servo.h>

Servo myservo;

nRF24L01p receiver(7, 8); //CSN,CE
int buzz = 2;
int B = 5;
int B2 = 6;
int C = 3;
int C2 = 10;
int led1 = 19;
int led2 = 18;

void setup() {

  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
  pinMode(buzz, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(9);
}

int comandos[9];


void loop() {
  if (receiver.available()) {
    receiver.read();
    receiver.rxPL(comandos, 9);
    //  Serial.print("Valor Recebido: ");
    interpreta();
    //    for (int i = 0; i < 9; i++) {
    //     Serial.print(comandos[i]);
    //    Serial.print(" - ");
    //  }
    //  Serial.println();
  }

  //delay(1);
}

void interpreta() {
  digitalWrite(buzz, comandos[8]);
  myservo.write(comandos[0]);

  if (comandos[1] <= 135 && comandos[1] >= 125) {
    digitalWrite(B, 0);
    digitalWrite(B2, 0);
    digitalWrite(C, 0);
    digitalWrite(C2, 0);
  } else if (comandos[1] > 135) {
    digitalWrite(B, 0);
    analogWrite(B2, map(comandos[1], 135, 255, 0, 255));
    digitalWrite(C, 0);
    analogWrite(C2, map(comandos[1], 135,255, 0, 255));
  } else {
    digitalWrite(B2, 0);
    analogWrite(B, map(comandos[1], 125, 0, 0, 255));
    digitalWrite(C2, 0);
    analogWrite(C, map(comandos[1], 125, 0, 0, 255));
  }
digitalWrite(led1, comandos[2]);
digitalWrite(led2, comandos[4]);
  
if(comandos[3]){
  digitalWrite(C, 0);
  digitalWrite(C2, 1);
    digitalWrite(B, 1);
  digitalWrite(B2, 0);
}
if(comandos[5]){
  digitalWrite(B, 0);
  digitalWrite(B2, 1);
  digitalWrite(C, 1);
  digitalWrite(C2, 0);
}




}


