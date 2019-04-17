#include <EEPROM.h>
#include <IRremote.h>
IRrecv irrecv(7);
decode_results results;
int bot_conf = 12;
boolean A=false,B=false;
int led = 13;
void setup()
{
  Serial.begin(9600);
   pinMode(bot_conf,INPUT_PULLUP);
   pinMode(led,OUTPUT);
   
   irrecv.enableIRIn(); 
 
     if (!digitalRead(bot_conf)) {
    Serial.println("Configuracao iniciada");
    while (!digitalRead(bot_conf)) {}
    captura();    
    }
   
   
}
void loop()
{   
      if(irrecv.decode(&results))
 {
   irrecv.resume(); 
   if(!A)
   A = (results.value == EEPROMReadlong(0)?true:false);
   if(A)
   B = (results.value == EEPROMReadlong(5)?true:false);
 }
  
  if(A && B){
   digitalWrite(led,!digitalRead(led));
  A,B = false; 
  }
    
    
    
}
void captura(){
long codigo_1, codigo_2;
  boolean gravar = true;
  while(gravar)
    if(irrecv.decode(&results))
 {
   irrecv.resume(); 
   codigo_1 = (codigo_1 == 0?results.value:codigo_1);
   codigo_2 = (codigo_1 == results.value?0:results.value);
   
   if(codigo_2){gravar = false;
   Serial.println("Capturado com sucesso");
   Serial.print("Codigo 1: ");
   Serial.println(codigo_1);
   Serial.print("Codigo 2: ");
   Serial.println(codigo_2);
    EEPROMWritelong(0, codigo_1);
    EEPROMWritelong(5, codigo_2);
 }
 }
}
void EEPROMWritelong(int address, long value)
{
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
long EEPROMReadlong(long address)
{
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
