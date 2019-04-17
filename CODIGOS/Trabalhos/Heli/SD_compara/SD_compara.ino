
#include <SD.h>
#include<SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 5); // RX, TX




File myFile;
int quant;
void setup() {
pinMode(7,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("SD iniciado");
  quant = quantidade();
    Serial.println(quant);
}

void loop() {
  if (mySerial.available()) {
    String comando = mySerial.readString();
    boolean x = getData(comando);
    if (x) {
      Serial.println("True");
    }else{
      Serial.println("False");
    }
  }



}


boolean getData(String id)
{
  String data = "";
boolean g = false;
  if (SD.exists("sms.txt")) {
    myFile = SD.open("sms.txt");

    if (myFile) {

      while (myFile.available()) {

        for (int i = 0; i <= quant; i++) {
          while (myFile.read() != '\n') {}

          char c = myFile.read();


          while (c != '|') {
            data = data + c;
            c = myFile.read();
          }
        
        if(id == data){
          
        myFile.close();
        return (true);
        }
         
          data = "";
        }
        myFile.close();
        return (false);
      }
      
    } else Serial.println("Erro ao abrir o arquivo");
  }
  else Serial.println("Arquino nao existe");
  
}

int quantidade() {
  myFile = SD.open("sms.txt");
  String num = "";
  if (myFile) {
    char f = myFile.read();

    while (f != '&') {
      num = num + f;
      f = myFile.read();
    }

    myFile.close();
    return num.toInt()-1;
  } else Serial.println("Erro ao abrir o arquivo");

}


