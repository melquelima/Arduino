#include <EtherCard.h>
#include <TimerOne.h>

int NOT = 8;
int ENABLE = 6;
int corr = 1;
int flag_nota = 0;
int R1 = A3;
int R2 = A4;
int R3 = A5;
int btn_cor = 7;
boolean flag_ping = 0;
boolean verm_pisca = 0;

unsigned long int pisca  = 0;
unsigned long int t_ping = 0;
unsigned long int t_cor = 0;


void setup () {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, 1);
  pinMode(NOT, INPUT);
  pinMode(btn_cor, INPUT_PULLUP);

  config_leds();
  Serial.begin(9600);
  cor(8);
  executa_cor2();

  while (!config_ethernet()) {
    cor(1);
    executa_cor2();
  }

  cor(3);
  executa_cor2();

  digitalWrite(ENABLE, 1);

  Serial.println();

  Timer1.initialize(100); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt(loop2); // attach the service routine here

}

void loop() {
  EN_PING();
  if (!flag_nota) {
    if (flag_ping) {
      if ((millis() - t_cor >= 60000) & digitalRead(btn_cor)) {
        t_cor = millis();
        cor(corr);
        fade();
        corr = (corr != 9 ? corr + 1 : 1);
      }else if(!digitalRead(btn_cor)){
        cor(4);
        executa_cor2();
      }
    }
    else {
      if (millis() - pisca >= 1000) {
        cor((verm_pisca == 0 ? 1 : 10));
        verm_pisca = !verm_pisca;
        executa_cor2();
        pisca = millis();
      }
    }
  }



}






