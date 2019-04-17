#include <Servo.h> 
#include <Ultrasonic.h>

Servo servo;
Ultrasonic ultrasonic; 

void setup()
{
  Serial.begin(9600);
servo.attach(9);
ultrasonic.attach(12,11); // (Trig PIN,Echo PIN)
servo.write(90);
}

void loop()
{
  delay(2000);
  if (ultrasonic.Ranging(CM)>=30)
  {
    Serial.println("Frente ON");
    delay(200);
    //motor ON
  }
  else if (ultrasonic.Ranging(CM)<30)
  {
    Serial.println("Frente OFF");
    servo.write(0);  //Girar para Esquerda
    delay(15);
    delay(2000);
    {
      if (ultrasonic.Ranging(CM)>=30)
      {
        Serial.println("Esquerda ON");
        servo.write(90);
        delay(15);
        //Esquerda ON
      }
        else if(ultrasonic.Ranging(CM)<30)
        {
          Serial.println("Esquerda OFF");
          servo.write(180);
          delay(15);
          delay(2000);
            
            if (ultrasonic.Ranging(CM)>=30)
            {
              Serial.println("Direita ON");
              servo.write(90);
              delay(15);
              delay(2000);
            }
              else if(ultrasonic.Ranging(CM)<30)
            {
              Serial.println("Direita OFF");
              servo.write(100);
              delay(15);
              delay(2000);
            }
        }
      }
    }
  }

