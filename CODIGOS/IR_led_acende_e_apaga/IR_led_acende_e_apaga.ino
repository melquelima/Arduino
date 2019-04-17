#include <IRremote.h>
int RECV_PIN =10;
IRrecv irrecv(RECV_PIN);
decode_results results;
int led1 = 9;
void setup()
{
  Serial.begin(9600);
irrecv.enableIRIn();
pinMode(led1,OUTPUT);
}
void loop()
{
 if(irrecv.decode(&results))
 {
   Serial.println(results.value,DEC);
   irrecv.resume();
   
  if (results.value ==16724175)
   {
   digitalWrite(led1,HIGH);
   }
  else if (results.value ==16753245)
   {
     digitalWrite(led1,LOW);
   }
}
}
