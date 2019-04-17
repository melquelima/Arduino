#include <SPI.h>
#include <nRF24L01p.h>
#include <SoftwareServo.h>

nRF24L01p receiver(8,7);//CSN,CE

int servo_pins[7] = {A0,A1,A2,A3,A4,A5,9};
SoftwareServo servos[7];


void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(80);
  receiver.RXaddress("Artur");
  receiver.init();
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  for(int i = 0;i<7;i++){
    servos[i].attach(servo_pins[i]);
    servos[i].setMaximumPulse(2200);  
}
//servos[2].write(90);
//delay(1000);
//servos[6].write(70);
}

byte myData[7];

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myData,7);
    digitalWrite(3,1);
    digitalWrite(4,1);
    for(int i = 0;i<7;i++){
      servos[i].write(myData[i]);
    }
  }
  digitalWrite(3,0);
    digitalWrite(4,0);
  SoftwareServo::refresh();
}
