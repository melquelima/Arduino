#include <SPI.h>
#include <SD.h>

File myFile;
File myFile2;
int quant;
void setup() {

  Serial.begin(9600);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  quant = quantidade();
  excluir("heli");
 
  


}

void loop() {


}

void excluir(String x) {
  if (verifica(x)) {
    SD.remove("copy.txt");
    String data = "";

    myFile2 = SD.open("copy.txt", FILE_WRITE); // cria o arquivo
    myFile2.print(quant);
    myFile2.println("&");

    if (padrao(1)) {
      while (myFile.available()) {
        for (int i = 0; i <= quant; i++) {
          while (myFile.read() != '\n') {}
          char c = myFile.read();


          while (c != '|') {
            data = data + c;
            c = myFile.read();
          }
          if (i == quant or quant == 1) {
            if (data != x) {
              myFile2.print(data);
              myFile2.print("|");
              Serial.println("ok1");
            }
          } else if (data != x) {
            myFile2.print(data);
            myFile2.println("|");
            Serial.println("ok1");
          }
          data = "";
        }
      }
      myFile.close();
      myFile2.close();
    }



    atualiza();
  }
}

void atualiza() {
  SD.remove("sms.txt");
  String data = "";
  myFile2 = SD.open("sms.txt", FILE_WRITE); // cria o arquivo
  myFile2.print(quant);
  myFile2.println("&");


  if (SD.exists("copy.txt")) { // abre o original
    myFile = SD.open("copy.txt");
    if (myFile) {
      while (myFile.available()) {
        for (int i = 0; i <= quant - 1; i++) {
          while (myFile.read() != '\n') {}
          char c = myFile.read();


          while (c != '|') {
            data = data + c;
            c = myFile.read();
            Serial.println("ok");
          }
          if (i == quant - 1) {
            myFile2.print(data);
            myFile2.print("|");
          } else {
            myFile2.print(data);
            myFile2.println("|");
          }

          data = "";
        }
      }
      myFile.close();
      myFile2.close();

    } else {
      Serial.println("Erro ao abrir o arquivo");
      return;
    }

  } else {
    Serial.println("arquivo nao existe");
    myFile2.close();
    SD.remove("copy.txt");
  }
  quant = quantidade();

  SD.remove("copy.txt");
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
    return num.toInt() - 1;
  } else Serial.println("Erro ao abrir o arquivo");

}

boolean verifica(String x) {
  String data = "";

  if (padrao(1)) {
    while (myFile.available()) {
      for (int i = 0; i <= quant; i++) {
        while (myFile.read() != '\n') {}
        char c = myFile.read();


        while (c != '|') {
          data = data + c;
          c = myFile.read();
        }

        if (data == x) {
          return true;
        }
        data = "";
      }

    }
    myFile.close();
  }
  return false;
}




boolean padrao(int x) {
  if (x) {
    if (SD.exists("SMS.txt"))
      myFile = SD.open("SMS.txt");
    if (myFile) {
      return true;
    }
  } else {
    if (SD.exists("COPY.txt"))
      myFile = SD.open("COPY.txt");
    if (myFile) {
      return true;
    }
  }
  return false;

}
