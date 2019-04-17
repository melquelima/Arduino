#include <VarSpeedServo.h>

#include <SPI.h>
#include <nRF24L01p.h>

VarSpeedServo myservo;
VarSpeedServo myservo2;


int servoValue; // variável do potenciometro lido no TX (FRENTE E RÉ)
int serv2;


int led =7;
int led2 =8;
nRF24L01p receiver(6, 4); //CSN,CE

void setup() {

  myservo.attach(9);
  myservo2.attach(10);
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  digitalWrite(led,1);
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
}
int comandos[4];
int controle = true;
void loop() {
  if(controle){
  if (receiver.available()) {
    receiver.read();
    for (int i = 0; i < 4; i++) {
      receiver.rxPL(comandos[i]);
    }
    printa();
    servos();
  }
  }else{
  myservo.write(map(analogRead(A0),0,1024,0,175),255,false);
  myservo2.write(map(analogRead(A1),0,1024,0,175),255,false);  
  }
  
if(!digitalRead(2)){
  controle = !controle;
  digitalWrite(led,controle);
  digitalWrite(led2,!digitalRead(led));
  while(!digitalRead(2)){}
  delay(200);
}

}
void servos() {
myservo.write(comandos[0],comandos[1],false);
myservo2.write(comandos[2],comandos[3],false);
}

void printa() {

  Serial.print("S1: ");
  Serial.print(comandos[0]);
  Serial.print(" vel: ");
  Serial.print(comandos[1]);
  Serial.print(" -- S2: ");
  Serial.print(comandos[2]);
  Serial.print(" vel: ");
  Serial.println(comandos[3]);


}












