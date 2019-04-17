#include <SPI.h>
#include <RFID.h>
#define RST 9
#define SS 10
RFID rfid(SS, RST); 
String senha = "201111449226";
String tag = "";

void setup(){ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
 }
void loop(){   
  
    if (rfid.isCard()){
        pega_tag();
        acesso(tag);
        delay(50);
      }
}

void pega_tag(){
  tag = ""; 
   if (rfid.readCardSerial())
      for(int i = 0;i<5;i++)tag += rfid.serNum[i];

 rfid.halt();
}

void acesso(String x){
  if(x == senha)
    Serial.println("acesso liberado");
else
  Serial.println("acesso negado");
}
