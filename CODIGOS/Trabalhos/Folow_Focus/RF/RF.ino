#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(8, 7); //CSN,CE

#include <EEPROM.h>
#include <pcfXpand.h>
#include <Wire.h>
pcfXpand pcf(39, INPUT); // endereço do CI a ser lido
pcfXpand pcf_leds(38, OUTPUT); // endereço do CI a ser ligado os leds


int count = 0; //variavel a receber a quantidade de pulsos
boolean comando = true; // variavel que determina a função a ser executada

int foco_max = EEPROM.read(11);
int foco_min = EEPROM.read(10);
int zoom_max = EEPROM.read(9);
int zoom_min = EEPROM.read(8);
//int foco_max = 170;
//int foco_min = 0;
//int zoom_max = 170;
//int zoom_min = 0;

int pot_foco = 0;
int pot_zoom = 1;
int pot_foco_ant = 0;
boolean ativo = 1;
boolean ativo_zoom = 1;
int bot_desativa, bot_desativa2, velocidade;

int comandos[4];

void setup() {
  // RF
pinMode(5,OUTPUT);
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
  
  delay(150);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);
  transmitter.TXaddress("Artur");
  transmitter.init();


  // Sketch
  Serial.begin(9600);
  pcf_leds.inicio('A');

for(int i =1;i<=6;i++)
pcf_leds.digWrite(i,0);
analogWrite(5,5);
delay(300);

for(int i =1;i<=6;i++)
pcf_leds.digWrite(i,1);
analogWrite(5,0);
}

void loop() {
  ler();

  if (ativo) {
    comandos[0] = map(analogRead(A0), 0, 1023, foco_min, foco_max);
    comandos[1] = 255;
    
    Serial.print("A0: ");
    Serial.print(comandos[0]);
    delay(15);
  }

  if (ativo_zoom) {
    comandos[2] = map(analogRead(A1), 0, 1023, zoom_min, zoom_max);
    comandos[3] = 255;
   // send(2, map(analogRead(A1), 0, 1023, zoom_min, zoom_max), 255);
    Serial.print(" A1: ");
    Serial.print(comandos[2]);
    delay(15);
  }

  if (pcf.digRead() == 7) { // configura ponto ZOOM MAX
    int tempo = 0;
    boolean sai = false;
    while (pcf.digRead() == 7 && !sai) { // verifica se o botao segurado por 3s
      tempo = tempo + 1;
      delay(10);
      if (tempo >= 300) {
        sai = true;
      }
    }
    if (tempo >= 300) {
      zoom_max = map(analogRead(A1), 0, 1023, 0, 170);
      EEPROM.write(9, zoom_max);
      Serial.print("Zoom Max: ");
      Serial.println(zoom_max);
      analogWrite(5,100);
      while (pcf.digRead() == 7) {}
      analogWrite(5,0);
    }
  }

  if (pcf.digRead() == 8) { // configura ponto ZOOM MIN
    int tempo = 0;
    boolean sai = false;
    while (pcf.digRead() == 8 && !sai) { // verifica se o botao segurado por 3s
      tempo = tempo + 1;
      delay(10);
      if (tempo >= 300) {
        sai = true;
      }
    }
    if (tempo >= 300) {
      zoom_min = map(analogRead(A1), 0, 1023, 0, 170);
      EEPROM.write(8, zoom_min);
      Serial.print("Zoom Min: ");
      Serial.println(zoom_min);
      analogWrite(5,100);
      while (pcf.digRead() == 8) {}
      analogWrite(5,0);
    }
  }

// ___________CONFIGURA FOCO________________

if (!digitalRead(2)) { // configura ponto FOCO MAX
    int tempo = 0;
    boolean sai = false;
    while (!digitalRead(2) && !sai) { // verifica se o botao segurado por 3s
      tempo = tempo + 1;
      delay(10);
      if (tempo >= 300) {
        sai = true;
      }
    }
    if (tempo >= 300) {
      foco_max = map(analogRead(A0), 0, 1023, 0, 170);
      EEPROM.write(11, foco_max);
      Serial.print("FOCO Max: ");
      Serial.println(foco_max);
      analogWrite(5,100);
      while (!digitalRead(2)) {}
      analogWrite(5,0);
    }
  }

  if (!digitalRead(3)) { // configura ponto FOCO MIN
    int tempo = 0;
    boolean sai = false;
    while (!digitalRead(3) && !sai) { // verifica se o botao segurado por 3s
      tempo = tempo + 1;
      delay(10);
      if (tempo >= 300) {
        sai = true;
      }
    }
    if (tempo >= 300) {
      foco_min = map(analogRead(A0), 0, 1023, 0, 170);
      EEPROM.write(11, foco_min);
      Serial.print("Foco Min: ");
      Serial.println(foco_min);
      analogWrite(5,100);
      while (!digitalRead(3)) {}
      analogWrite(5,0);
    }
  }



//____________FIM CONFIGURA FOCO___________

velocidade = map(analogRead(A2), 0, 1023, 255, 10);
  Serial.print(" Velocidade : ");
  Serial.println(velocidade);

send();
}
void send(){
 for (int i = 0;i<6;i++){
  transmitter.txPL(comandos[i]);
 }
 transmitter.send(SLOW);
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
          pcf_leds.digWrite(i + 1, 1);
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
      EEPROM.write(B, map(analogRead(A0), 0, 1023, 170, 0));
    }
    else {
      EEPROM.write(B, map(analogRead(A1), 0, 1023, 0, 170));
    }
    Serial.print("Gravado: ");
    Serial.println(EEPROM.read(B));
  } else {
    if (B >= 4) //botoes verde e servo de foco
      if (!bot_desativa) {
        bot_desativa = B;
        compara(0);
        leds_comando2(B, 1);
        comandos[0] = EEPROM.read(B);
        comandos[1] = velocidade;
      }
      else {
        if (B == bot_desativa) {
          compara(1);
          bot_desativa = 0;
          leds_comando2(B, 0);
        } else {
          bot_desativa = B;
          leds_comando2(B, 1);
          comandos[0] = EEPROM.read(B);
          comandos[1] = velocidade;
        }
      } else { //botoes vermelhos e servo de zoom
      if (!bot_desativa2) {
        bot_desativa2 = (B == 0 ? 6 : B);
        compara2(0);
          comandos[2] = EEPROM.read(B);
          comandos[3] = velocidade;
        leds_comando(B, 1);
      }
      else {
        if (B == bot_desativa2) {
          compara2(1);
          bot_desativa2 = 0; leds_comando(B, 0);
        } else {
          bot_desativa2 = B;
          comandos[2] = EEPROM.read(B);
          comandos[3] = velocidade;
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
int servoValue;
int serv2;


