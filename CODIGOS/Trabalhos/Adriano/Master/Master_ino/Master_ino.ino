#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(5, 7); //CSN,CE

int portas[8]={2,3,4,6,16,9,14,15};// portas para cada botao

int valores[8];
void setup() {

  for(int i=0;i<8;i++)
    pinMode(portas[i],INPUT_PULLUP);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();
  Serial.begin(9600);
  
 
}

void loop() {

  for(int i=1;i<9;i++){
    if(!digitalRead(portas[i-1])){
    valores[i-1] = !valores[i-1];
  while(!digitalRead(portas[i-1])){};  
  }
  }
     transmitter.txPL(valores,8);
     transmitter.send(FAST);  
     
          
     
    Serial.print(valores[0]);
    Serial.print(valores[1]);
    Serial.print(valores[2]);
    Serial.print(valores[3]);
    Serial.print(valores[4]);
    Serial.print(valores[5]);
    Serial.print(valores[6]);
    Serial.println(valores[7]);

    
}
