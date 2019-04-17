
#include <Servo.h> 
Servo myservo;
int rele = 12;

void setup()
{
myservo.attach(9);
pinMode(rele,OUTPUT);
}

void loop()
{
 myservo.write(0);
 digitalWrite(rele, HIGH);
 delay(2000);
 digitalWrite(rele, LOW);
 delay(2000);
 myservo.write(180);
 digitalWrite(rele, HIGH);
 delay(2000); 
 digitalWrite(rele,LOW);
 delay(2000);
}

