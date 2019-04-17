#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 2); // RX, TX
int state = 0;
unsigned long int now = millis();

void setup()  
{
  mySerial.begin(9600);
  pinMode(0,OUTPUT);
}

void loop() // run over and over
{
  if(mySerial.available()){
    if (mySerial.read() == '$'){
      now = millis();
    }
  }  

  if((millis()-now)<500){
    digitalWrite(0,1);
  }else{
    digitalWrite(0,0);
  }

}




