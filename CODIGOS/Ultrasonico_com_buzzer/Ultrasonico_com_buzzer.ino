#include <Ultrasonic.h>
int buzzer = 5;
Ultrasonic ultrasonic;
const int turn=0;
void setup()
{
  Serial.begin(9600);
  delay(200);
  pinMode(buzzer,OUTPUT);
  ultrasonic.attach(12,11);
}
void loop()
{
  Serial.println(ultrasonic.Ranging(CM));
  delay(200);
 if ((ultrasonic.Ranging(CM)<100)&(ultrasonic.Ranging(CM)>30))
  {
 digitalWrite(buzzer,HIGH);
 delay(100);
 digitalWrite(buzzer,LOW);
delay(100);
}
else if (ultrasonic.Ranging(CM)<30)
{
  digitalWrite(buzzer,HIGH);
 delay(50);
 digitalWrite(buzzer,LOW);
delay(50);
}

}
