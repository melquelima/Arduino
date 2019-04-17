/********************************************************
** Download from:                                      **
** http://www.alhin.de/arduino/index.php?n=53          **
********************************************************/

#include <AH_74HC595.h>

#define SER_Pin 4   //Serial data input
#define RCLK_Pin 3  //Register clock
#define SRCLK_Pin 2 //Shift register clock

//Initialisation
AH_74HC595 shifter(SER_Pin, RCLK_Pin, SRCLK_Pin); 
int tempo;
int a=0;

void setup(){
tempo=300;
Serial.begin(9600);
}

void loop(){
tempo=tempo-20;
shifter.clear();  
  for(int a = 0; a <= 5 ; a ++){
  shifter.setPin(a,HIGH);
  shifter.setPin(a+1,HIGH);
  shifter.setPin(a+2,HIGH);
  if (a != 0){shifter.setPin(a-1,LOW);}
  delay(tempo);
  } 
  
    for(int a = 7; a >= 2 ; a --){
  shifter.setPin(a,HIGH);
  shifter.setPin(a-1,HIGH);
  shifter.setPin(a-2,HIGH);
  shifter.setPin(a+1,LOW);
  delay(tempo);
  }
  Serial.println(tempo);
  if (tempo <=20){tempo=40; a++;if (a==30){a=0; tempo=300;}
Serial.println(a);
}  

  
  
}

