#include <IRremote.h>
int RECV_PIN =10;
IRrecv irrecv(RECV_PIN);
decode_results results;
int Led = 13;
int estado =0;
boolean set = false;
void setup() {
  irrecv.enableIRIn();
pinMode(Led,OUTPUT);
Serial.begin(9600);

}

void loop() {
  if(irrecv.decode(&results))
 {
   Serial.println(results.value,DEC);
   irrecv.resume();
if (results.value ==16724175){
 if (set == false){
    set = true; 
  }
  else{
   set = false;
   delay(10);
  
  }
  
  if (set == false){
  digitalWrite(Led,HIGH);
  }
  else{
   digitalWrite(Led,LOW); 
  }
 }
}
}
