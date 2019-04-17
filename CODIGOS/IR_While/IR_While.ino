
#include <Servo.h> 
Servo myservo;
#include <IRremote.h>
int RECV_PIN =10;
IRrecv irrecv(RECV_PIN);
decode_results results;
int rele = 12;

void setup()
{
Serial.begin(9600);
myservo.attach(9);
pinMode(rele,OUTPUT);
irrecv.enableIRIn();
}

void loop()
{
  if(irrecv.decode(&results))
  {
  Serial.println(results.value,DEC);
  irrecv.resume();
  
 while(results.value ==16724175)
 {
   digitalWrite(rele,HIGH);
 }
  digitalWrite(rele,LOW); 
  }
}

