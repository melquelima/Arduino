
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX

int portas[6] = {
  7,2,5,3,4,6};
char comandos[7]={
  's','%','<','c','>','b','!'};
int aut = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  for(int i =0;i<6;i++){
    pinMode(portas[i],INPUT_PULLUP);
  }
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() // run over and over
{

  for(int i =0;i<6;i++){
    if(!digitalRead(portas[i])){
      if(i <=1){
        mySerial.write(comandos[i]);
        Serial.println(comandos[i]);
        delay((aut ==1?1:500));
        aut = i;
      }
      else{

        mySerial.write(comandos[i]);
        Serial.println(comandos[i]);
        delay(1);
        while(!digitalRead(portas[2])){
        };
        while(!digitalRead(portas[4])){
        };
        if(i == 2|| i == 4){
          mySerial.write(comandos[6]);
          Serial.println(comandos[6]);  
        }

      }
    }
  }
  if (Serial.available())
    mySerial.write(Serial.read());
}



