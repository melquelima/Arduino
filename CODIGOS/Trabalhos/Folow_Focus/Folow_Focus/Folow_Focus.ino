#include <VarSpeedServo.h>

#include <EEPROM.h>
#include <pcfXpand.h>
#include <Wire.h>
VarSpeedServo myservo;
VarSpeedServo myservo2;
pcfXpand pcf(39, INPUT); // endereço do CI a ser lido
pcfXpand pcf_leds(38, OUTPUT); // endereço do CI a ser ligado os leds


int count = 0; //variavel a receber a quantidade de pulsos
boolean comando = true; // variavel que determina a função a ser executada

//int foco_max = EEPROM.read(9);
//int foco_min = EEPROM.read(7);
int zoom_max = EEPROM.read(10);
int zoom_min = EEPROM.read(8);
//int zoom_max = 170;
//int zoom_min = 0;
int foco_max = 170;
int foco_min = 0;

int pot_foco = 0;
int pot_zoom = 1;
int pot_foco_ant = 0;
boolean ativo = 1;
boolean ativo_zoom = 1;
int bot_desativa;
int bot_desativa2;
int velocidade;

void setup() {

  // put your setup code here, to run once:
  myservo.attach(9);
  myservo2.attach(11);
  Serial.begin(9600);
pcf_leds.inicio('A');

}

void loop() {
  ler();

  if (ativo) {
    myservo.write(map(analogRead(A0), 0, 1023, foco_min, foco_max));
    Serial.print("A0: ");
    Serial.print(analogRead(A0)/6);
    delay(15);
  }
  
  if (ativo_zoom) {
    myservo2.write(map(analogRead(A1), 0, 1023, zoom_min, zoom_max));
    Serial.print(" A1: ");
    Serial.print(analogRead(A1)/6);
    delay(15);
  }
  
  if(pcf.digRead() == 7){ // configura ponto ZOOM MAX
     int tempo = 0;
     boolean sai = false;
     while(pcf.digRead() == 7 && !sai){ // verifica se o botao segurado por 3s
      tempo = tempo + 1;
      delay(10);
      if (tempo >= 300){sai = true;}
     }
     if (tempo >= 300){
     zoom_max = map(analogRead(A1), 0, 1023, 0, 170); 
     EEPROM.write(10,zoom_max);
     Serial.print("Zoom Max: ");
     Serial.println(zoom_max);
     while(pcf.digRead() == 7){}
     }
  }
  
      if(pcf.digRead() == 8){ // configura ponto ZOOM MIN
     int tempo = 0;
     boolean sai = false;
     while(pcf.digRead() == 8 && !sai){ // verifica se o botao segurado por 3s
      tempo = tempo + 1;
      delay(10);
      if (tempo >= 300){sai = true;}
     }
     if (tempo >= 300){
     zoom_min = map(analogRead(A1), 0, 1023, 0, 170); 
     EEPROM.write(8,zoom_min);
     Serial.print("Zoom Min: ");
     Serial.println(zoom_min);
     while(pcf.digRead() == 8){}
     }
  }
  

  velocidade = map(analogRead(A2),0,1023,255,10);
  Serial.print(" Velocidade : ");
  Serial.println(velocidade);
}

void ler() {

  for (int i = 0; i < 6; i++ )
    if (pcf_ler(i)) {  //se o botao for pressionado
      count = 0;                //zera count
      while (pcf_ler(i)) { // enquanto o totao estiver pressionado
        count++;             // adciona mais 1 a count
        delay(200);           // espera 200milisegundos
        if (count == 10) {    // verifica se count eigual a 10 se for
          pcf_leds.digWrite(i + 1, 0);
          acao(i, 2);
          comando = false;       // indica que a outra função nao sera executada
          while (pcf_ler(i)) {} // espera o usuario tirar o dedo do botao
          pcf_leds.digWrite(i+1, 1);
        }
      }
      if (comando)  // se comando for igual a true
        acao(i, 1);
      comando = true;   // seta comando como true
    }

}

void acao(int B, int A) {
  B = B + 1;
  if (A == 2) {
    if (B >= 4) {
      EEPROM.write(B, analogRead(A0) / 6);
    }
    else {
      EEPROM.write(B, analogRead(A1) / 6);
    }
    Serial.print("Gravado: ");
    Serial.println(EEPROM.read(B));
  } else {
    if (B >= 4) //botoes verde e servo de foco
      if (!bot_desativa) {
        bot_desativa = B;
        compara(0);
        leds_comando2(B, 1);
        myservo.write(EEPROM.read(B),velocidade,false);
      }
      else {
        if (B == bot_desativa) {
          compara(1);
          bot_desativa = 0;
          leds_comando2(B, 0);
        } else {
          bot_desativa = B;
          leds_comando2(B, 1);
          myservo.write(EEPROM.read(B),velocidade,false);
        }
      } else { //botoes vermelhos e servo de zoom
      if (!bot_desativa2) {
        bot_desativa2 = (B == 0 ? 6 : B);
        compara2(0);
        myservo2.write(EEPROM.read(B),velocidade,false);
        leds_comando(B, 1);
      }
      else {
        if (B == bot_desativa2) {
          compara2(1);
          bot_desativa2 = 0; leds_comando(B, 0);
        } else {
          bot_desativa2 = B;
          myservo2.write(EEPROM.read(B),velocidade,false);
          leds_comando(B, 1);
        }
      }
    }

  }
  Serial.print("Botao : ");
  Serial.print(B);
  Serial.print(" acao : ");
  Serial.println(A);


  delay(300);
}

void compara (int valor) {
  if (valor == 1) {
    ativo = 1;
  }
  else {
    ativo = 0;
  }
}

void compara2 (int valor) {
  if (valor == 1) {
    ativo_zoom = 1;
  }
  else {
    ativo_zoom = 0;
  }
}

boolean pcf_ler(int bot) {
  bot = bot + 1;
  int ler = pcf.digRead();
  int leitura = (ler != 0 ? ler : 9);

  if (bot == leitura) {
    return true;
  }
  else {
    return false;
  }
}

void leds_comando(int led, boolean estado) {
  for (int j = 1; j <= 3; j++ ) {
    pcf_leds.digWrite(j, 1);
  }
  pcf_leds.digWrite(led, !estado);
}

void leds_comando2(int led, boolean estado) {

  for (int j = 4; j <= 6; j++ ) {
    pcf_leds.digWrite(j, 1);
  }
  pcf_leds.digWrite(led, !estado);
}



