#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
//#include <Servo.h> 

//Servo myservo;  // create servo object to control a servo 

TMRpcm tmrpcm;   // create an object for use in this sketch

unsigned long time = 0;

int habilita = true;

void setup(){

  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  Serial.begin(115200);
  pinMode(13,OUTPUT); //LED Connected to analog pin 0
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not

  }
  else{   
    Serial.println("SD ok");   
  }

  tmrpcm.volume(1);
  tmrpcm.volume(1);
  tmrpcm.play("grito.wav");
}



void loop(){  

}



