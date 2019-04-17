#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 3); // RX, TX



int M1A = 5;
int M1B = 6;
int M1AS = 0;
int M1BS = 0;

int M2A = 10;
int M2B = 9;
int M2AS = 0;
int M2BS = 0;


void setup(){
  
  pinMode(M1A,OUTPUT);
  pinMode(M1B,OUTPUT); 
  pinMode(M2A,OUTPUT);
  pinMode(M2B,OUTPUT);
  
  digitalWrite(M1A,0);
  digitalWrite(M1B,0);
  digitalWrite(M2A,0);
  digitalWrite(M2B,0);
  
  delay(1000);
  Serial.begin(9600);
  mySerial.begin(9600);
  
}
unsigned long contagem;

byte myData[24];
int last_press = 0;
int aceleracao;
boolean terminado = true;

void loop(){ 
  

  if(mySerial.available()){
    contagem = 0;
    char comando = mySerial.read();
    Serial.print("-----------------comando :");
    Serial.print(comando);
    Serial.write(comando);
    Serial.println();
    
    switch(comando){
     case 'U':
      myData[17] = 1;
     break;
    case 'D':
      myData[18] = 1;
     break;
    case 'L':
      myData[15] = 1;
     break;
    case 'R':
      myData[16] = 1;
     break;
     default:
     myData[17] = 0;
     myData[18] = 0;
     myData[15] = 0;
     myData[16] = 0;
    }
  }else{
   contagem ++; 
  }
  
  if(contagem >= 3000){
    myData[17] = 0;
     myData[18] = 0;
     myData[15] = 0;
     myData[16] = 0;
  }
  myData[20] = 0;
  // --------------------------- inicio
  //digitalWrite(4,myData[20]);
    
    int taxa = myData[20]?254:150;
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
      Serial.println("DIREITA");
      analogWrite(M1B,aceleracao);
      analogWrite(M2A,aceleracao);
      terminado = aceleracao==0?true:false;
    }  
    
    //analogWrite(M1A,(aceleracao > 0 && last_press == 17?aceleracao:aceleracao));
    //analogWrite(M2A,(aceleracao > 0 && last_press == 17?aceleracao:aceleracao));
    Serial.println(aceleracao);
    //Serial.println((myData[17] || myData[18]|| myData[15]|| myData[16]));
    //analogWrite(M1B,M1BS);
    //analogWrite(M2B,M2BS);
  
  
  
}


