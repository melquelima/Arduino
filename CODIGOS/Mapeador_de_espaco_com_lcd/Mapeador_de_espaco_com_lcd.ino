#include <Servo.h> 
#include <Ultrasonic.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

Servo servo;
Ultrasonic ultrasonic; 

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
servo.attach(7);
ultrasonic.attach(10,8); // (Trig PIN,Echo PIN)
servo.write(90);
}

void loop()
{
  delay(500);
  if (ultrasonic.Ranging(CM)>=60)
  {
    Serial.println("Frente ON");
    lcd.clear();
    lcd.print("Frente ON");
   
    //motor ON
  }
  else if (ultrasonic.Ranging(CM)<30)
  {
    Serial.println("Frente OFF");
        lcd.clear();
        lcd.print("Frente OFF");
    servo.write(0);  //Girar para Esquerda
    delay(15);
    delay(1000);
    {
      if (ultrasonic.Ranging(CM)>=30)
      {
        Serial.println("Esquerda ON");
        lcd.clear();
        lcd.print("Esquerda ON");
        servo.write(90);
        delay(15);
        //Esquerda ON
      }
        else if(ultrasonic.Ranging(CM)<30)
        {
          Serial.println("Esquerda OFF");
          lcd.clear();
          lcd.print("Esquerda OFF");
          servo.write(180);
          delay(15);
          delay(1000);
            
            if (ultrasonic.Ranging(CM)>=30)
            {
              Serial.println("Direita ON");
              lcd.clear();
              lcd.print("Direita ON");
              servo.write(90);
              delay(15);
              delay(1000);
            }
              else if(ultrasonic.Ranging(CM)<30)
            {
              Serial.println("Direita OFF");
              lcd.clear();
              lcd.print("Direita OFF");
              servo.write(100);
              delay(15);
              delay(1000);
            }
        }
      }
    }
  }

