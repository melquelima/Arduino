/*-------------IR--------------*/
#include <Servo.h>
Servo myservo;
/*------------ULTRASONICO-------*/
#include <Ultrasonic.h>
Ultrasonic ultrasonic;
float cmMsec;
/*-----------VARIAVEIS----------------*/
int Pin1 =2;    // LED connected to digital pin 9
int Pin2 =3;
int Pin3 =7;
int Pin4 =6;
int farol = 8;
int valor;
int ldr = A5;
int LED = 11;
int valMap = 0;
boolean Bfarol = false;

void setup()  { 
  // nothing happens in setup 
  Serial.begin(9600);
  myservo.attach(5);
  ultrasonic.attach(9,10);
  pinMode(Pin1,OUTPUT);
  pinMode(Pin2,OUTPUT);
  pinMode(Pin3,OUTPUT);
  pinMode(Pin4,OUTPUT);
  pinMode(farol,OUTPUT);
  digitalWrite(Pin1,HIGH);
  digitalWrite(Pin2,HIGH);
  digitalWrite(Pin3,HIGH);
  digitalWrite(Pin4,HIGH);
} 

void loop() {
  
delay(100);
valor = analogRead(ldr);
 Serial.println(valor);
 if (valor <50){analogWrite(LED,1023);}
 else{digitalWrite(LED,LOW);}


  if (ultrasonic.Ranging(CM)>=30)
  {
    Serial.println("Frente ON");
    digitalWrite(Pin1,LOW);
 digitalWrite(Pin2,HIGH); 
 digitalWrite(Pin3,HIGH);
 digitalWrite(Pin4,LOW);
    delay(200);
    //motor ON
  }
  else if (ultrasonic.Ranging(CM)<30)
  {
    Serial.println("Frente OFF");
    stopA();
    myservo.write(0);  //Girar para Esquerda
    delay(15);
    delay(500);
    {
      if (ultrasonic.Ranging(CM)>=30)
      {
        Serial.println("Esquerda ON");
        myservo.write(90);
        delay(15);
        //Esquerda ON
 digitalWrite(Pin4,LOW);
 digitalWrite(Pin3,HIGH); 
 delay(2000);
      }
        else if(ultrasonic.Ranging(CM)<30)
        {
          Serial.println("Esquerda OFF");
          myservo.write(180);
          delay(15);
          delay(500);
            
            if (ultrasonic.Ranging(CM)>=30)
            {
              Serial.println("Direita ON");
              myservo.write(90);
              delay(15);
              delay(500);
 digitalWrite(Pin2,HIGH);
 digitalWrite(Pin1,LOW);
 delay(2000);
            }
              else if(ultrasonic.Ranging(CM)<30)
            {
              Serial.println("Direita OFF");
              myservo.write(90);
              delay(15);
              delay(500);
              re(); 
              stopA();
 digitalWrite(Pin2,HIGH);
 digitalWrite(Pin1,LOW); 
delay(4000);
 
            }
        }
      }
    }
}

void re(){
digitalWrite(Pin1,HIGH);
 digitalWrite(Pin2,LOW); 
 digitalWrite(Pin3,LOW);
 digitalWrite(Pin4,HIGH);
 delay(2000);
}
 void stopA(){
   digitalWrite(Pin1,LOW);
 digitalWrite(Pin2,LOW); 
 digitalWrite(Pin3,LOW);
 digitalWrite(Pin4,LOW); 
 }
 
