// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"
int led = 13;
RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  pinMode(led,OUTPUT);
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop () {
    DateTime now = rtc.now();
    String relogio_data = "DT: ";
    String relogio_hora = "HR: ";
    
    int dia = now.day();
    int mes = now.month();
    int ano = now.year();
    int hora = now.hour();
    int minuto = now.minute();
    int segundos = now.second();
   
    
    relogio_data += ArrumaZero(dia);
    relogio_data += "/";
    relogio_data += ArrumaZero(mes);
    relogio_data += "/";
    relogio_data += ano;
       
    Serial.println (relogio_data);
    
    relogio_hora += ArrumaZero(hora);
    relogio_hora += ":";
    relogio_hora += ArrumaZero(minuto);
    relogio_hora += ":";
    relogio_hora += ArrumaZero(segundos);
    
   
    Serial.println (relogio_hora);

}


String ArrumaZero(int i){
 String ret;
 if(i <10){ret += "0";} 
  ret += i;
  return ret;
  
}
