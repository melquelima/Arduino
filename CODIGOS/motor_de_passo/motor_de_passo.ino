
/* 
 Stepper Motor Contro)&&(ld == 'a'){ion
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.  
 
  
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 
 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
                                     // for your motor
int ld;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(100);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()>0){
    ld = Serial.read();
  }
  
    if (ld == 'a'){
   Serial.println("clockwise");
  myStepper.step(200);
  ld = 0;
   }
 else if (ld == 'b'){
   Serial.println("counterclockwise");
  myStepper.step(-200);
  ld = 0;
  
 }
}

