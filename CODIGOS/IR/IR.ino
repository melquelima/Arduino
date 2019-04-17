#include <LiquidCrystal.h>
#include <IRremote.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int RECV_PIN =10;
IRrecv irrecv(RECV_PIN);
decode_results results;
int led1 = 9;
int led2 = 8;
int led3 = 7;
void setup()
{
Serial.begin(9600);
  lcd.begin(16,2);
irrecv.enableIRIn();
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
}
void loop()
{
 if(irrecv.decode(&results))
 {
   Serial.println(results.value,DEC);
   irrecv.resume();
   
   if (results.value ==16724175)
   {
     lcd.clear();
     Serial.println("LED1");
     lcd.print("LED1");
     digitalWrite(led1,HIGH);
     delay(1500);
     lcd.clear();
   }
   if (results.value ==16718055)
   {
     lcd.clear();
     Serial.println("LED2");
     lcd.print("LED2");
   digitalWrite(led2,HIGH);
 delay(1500);
 lcd.clear();}
     
     if (results.value ==16743045)
   {
     lcd.clear();
     Serial.println("LED3");
     lcd.print("LED3");
   digitalWrite(led3,HIGH);
 delay(1500);
 lcd.clear();}
   
   if (results.value ==16753245)
   {
     lcd.clear();
     Serial.println("LEDS OFF");
     lcd.print("LEDS OFF");
   digitalWrite(led1,LOW);
 digitalWrite(led2,LOW);
 digitalWrite(led3,LOW);
 delay(1000);
 lcd.clear();}
 
 
 
 }
}
