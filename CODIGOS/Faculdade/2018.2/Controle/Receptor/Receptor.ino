#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p receiver(7,8);//CSN,CE

void setup(){
  delay(150);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
}

byte myData[23];

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myData,23);
	
    //**Print received arrays**
    for(int it=0;it<23;it++){
      Serial.print(myData[it]);
      if(it!=22){
        Serial.print('\t');
      }else{
        Serial.println();
      }
    }
  }
}
