// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
int ler = 4;
int habilita = A0;

void setup() 
{
  pinMode(ler,INPUT);
  pinMode(habilita,OUTPUT); 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  } 

void loop() 
{ 
  if (digitalRead(ler)){
    digitalWrite(habilita,1);
    myservo.write(180);
    delay(800);
    digitalWrite(habilita,0);
    while(digitalRead(ler)){};
  }
  else{
    digitalWrite(habilita,1);
    myservo.write(90);
    delay(800);
    digitalWrite(habilita,0);
    
    while(!digitalRead(ler)){};
  }

  // waits for the servo to get there 
} 

