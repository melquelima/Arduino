#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
//#include <Servo.h> 
 
//Servo myservo;  // create servo object to control a servo 

TMRpcm tmrpcm;   // create an object for use in this sketch

unsigned long time = 0;


int reed = 2;
int led = 7;
int habilita = true;
int servo = 6;

void setup(){

  
  pinMode(led,OUTPUT);
  pinMode(servo,OUTPUT);
  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  //Complimentary Output or Dual Speakers:
  //pinMode(10,OUTPUT); Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45 
  pinMode(reed,INPUT_PULLUP);
  Serial.begin(115200);
  pinMode(13,OUTPUT); //LED Connected to analog pin 0
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not

  }
  else{   
    Serial.println("SD ok");   
  }
  digitalWrite(servo,0);
  //tmrpcm.volume(1);
  //tmrpcm.volume(1);
  //myservo.attach(6);
  //myservo.write(90);
  //delay(2000);
  //tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
 
  tmrpcm.play("choro.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
  //delay(7000);
  //tmrpcm.stopPlayback();

}



void loop(){  

  digitalWrite(led,digitalRead(reed));
  
  if(digitalRead(reed)&& habilita){
    digitalWrite(servo,1);
    tmrpcm.volume(1);
    tmrpcm.volume(1);
    tmrpcm.play("grito.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
    int tempo = 0;
    
    while(tempo <6000){
      digitalWrite(led,digitalRead(reed));    
      delay(1);
      tempo++;
    }
    tmrpcm.stopPlayback();    
    tmrpcm.volume(0);
    tmrpcm.volume(0);
    tmrpcm.play("choro.wav");
    delay(10);
    tmrpcm.stopPlayback();
    habilita = false;
    digitalWrite(servo,0);
  }

  //blink the LED manually to demonstrate music playback is independant of main loop
  if(habilita &&(millis() - time > 30000) ) {      
    tmrpcm.play("choro.wav");
    time = millis();    
  }
  if(!digitalRead(reed)&& !habilita){
    delay(1000);
    time = millis();
    habilita = true;
    tmrpcm.play("choro.wav");
  }  
  
}


