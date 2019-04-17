#include <SPI.h>
#include <nRF24L01p.h>
#include <SoftwareServo.h>

nRF24L01p receiver(8,7);//CSN,CE

int servo_pins[6] = {14,15,16,17,18,19};
SoftwareServo servos[6];


void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
  
  for(int i = 0;i<6;i++){
    servos[i].attach(servo_pins[i]);
    servos[i].setMaximumPulse(2200);  
}
}

byte myData[6];

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myData,6);
    for(int i = 0;i<6;i++){
      servos[i].write(myData[i]);
    }
  }
  SoftwareServo::refresh();
}
