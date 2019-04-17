#include <SPI.h>
#include <nRF24L01p.h>
#include <SoftwareServo.h>

nRF24L01p receiver(7,8);//CSN,CE

int M1A = 5;
int M1B = 6;
int M1AS = 0;
int M1BS = 0;

int M2A = 10;
int M2B = 9;
int M2AS = 0;
int M2BS = 0;


void setup(){
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);
  receiver.RXaddress("Artur");
  receiver.init();
  pinMode(4, OUTPUT);
  digitalWrite(4,0);
  
  pinMode(M1A,OUTPUT);
  pinMode(M1B,OUTPUT); 
  pinMode(M2A,OUTPUT);
  pinMode(M2B,OUTPUT);
  
  digitalWrite(M1A,0);
  digitalWrite(M1B,0);
  digitalWrite(M2A,0);
  digitalWrite(M2B,0);
  
  digitalWrite(4,1);
  delay(1000);
  digitalWrite(4,0);
  Serial.begin(9600);
  
}

byte myData[24];
int last_press = 0;
int aceleracao;
boolean terminado = true;

void loop(){ 
  if(receiver.available()){
    receiver.read();
    receiver.rxPL(myData,24);
    digitalWrite(4,myData[20]);
    
    int taxa = myData[20]?254:0000;
     aceleracao = ((myData[17] || myData[18]|| myData[15]|| myData[16])?(aceleracao==taxa?taxa:aceleracao + 2):(aceleracao==0?0:aceleracao - 2));
    
    last_press = terminado?(myData[17]?17:(myData[18]?18:(myData[15]?15:(myData[16]?16:0)))):last_press;
    
    
    //M1AS = myData[17] && M1BS ==0?aceleracao:M1AS;
    //M1BS =  myData[18] && M1AS ==0?aceleracao:M1BS;
    
    //M1AS = ((myData[17] || myData[15]) && M1BS ==0?(M1AS==taxa?taxa:M1AS + 2):(M1AS==0?0:M1AS - 2));
    //M1BS = (myData[18] && M1AS ==0?(M1BS==taxa?taxa:M1BS + 2):(M1BS==0?0:M1BS - 2));
    //M2AS = M1AS;
    //M2BS = M1BS;

    
    // frente
    
    if(last_press == 17){
      Serial.println("FRENTE");
      analogWrite(M1A,aceleracao);
      analogWrite(M2A,aceleracao);
      terminado = aceleracao==0?true:false;
    }

    if(last_press == 18){
      Serial.println("TRAZ");
      analogWrite(M1B,aceleracao);
      analogWrite(M2B,aceleracao);
      terminado = aceleracao==0?true:false;
    }    

    if(last_press == 15){
      Serial.println("ESQUERDA");
      analogWrite(M1A,aceleracao);
      analogWrite(M2B,aceleracao);
      terminado = aceleracao==0?true:false;
    }  
    
    if(last_press == 16){
      Serial.println("DOREITA");
      analogWrite(M1B,aceleracao);
      analogWrite(M2A,aceleracao);
      terminado = aceleracao==0?true:false;
    }  
    
    //analogWrite(M1A,(aceleracao > 0 && last_press == 17?aceleracao:aceleracao));
    //analogWrite(M2A,(aceleracao > 0 && last_press == 17?aceleracao:aceleracao));
    Serial.println(aceleracao);
    //analogWrite(M1B,M1BS);
    //analogWrite(M2B,M2BS);
  }
}


