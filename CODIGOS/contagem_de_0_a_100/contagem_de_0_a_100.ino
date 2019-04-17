/********************************************************
** Download from:                                      **
** http://www.alhin.de/arduino/index.php?n=53          **
********************************************************/

#include <AH_74HC595.h>

/*
#define SER_Pin   4   //Serial data input
#define RCLK_Pin  3   //Register clock
#define SRCLK_Pin 2   //Shift register clock
*/

//Initialisation
//AH_74HC595 seven_segment1(SER_Pin, RCLK_Pin, SRCLK_Pin); 
AH_74HC595 seven_segment1(4, 3, 2); 
AH_74HC595 seven_segment2(7, 6, 5);
AH_74HC595 seven_segment3(10, 9, 8);

void setup(){
// Serial.begin(9600);
 seven_segment1.clear();
 seven_segment2.clear();
seven_segment3.clear(); 

 for (int i=0;i<10;i++){
   seven_segment3.showNumber(i);
   for (int j=0;j<10;j++){
     seven_segment1.showNumber(j);
     for (int j=0;j<10;j++){
       seven_segment2.showNumber(j);
      delay(100); 
     }       
   }
 }   
 seven_segment1.setValue(1);
 seven_segment2.setValue(1);
seven_segment3.setValue(1); 
 delay(100);
}

void loop(){ 
 seven_segment1.rotate();
 seven_segment2.rotate();
 seven_segment3.rotate(); 
 delay(200);  
}

