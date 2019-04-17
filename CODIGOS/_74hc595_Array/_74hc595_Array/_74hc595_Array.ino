int DATA = 4;
int CLOCK = 2;
int LATCH = 3;
boolean dado[8] = {1,0,1,0,1,0,1,0};

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  atualiza();
}

void loop() {

}
void atualiza() {

  digitalWrite(LATCH, LOW); //permite o fluxo dos dados.

  for (int x = 15; x >=8; x--) {
    digitalWrite(CLOCK, LOW); //pronto para receber o bit.

    if (dado[x])digitalWrite(DATA, HIGH); //Grava o bit como 1
    else  digitalWrite(DATA, LOW); //Grava o bit como 0

    digitalWrite(CLOCK, HIGH); //grava o bit recebido.
  }
  digitalWrite(LATCH, HIGH); //finaliza o fluxo dos dados e envia os 8 bits.

// segundo CI ------------------


  digitalWrite(LATCH, LOW); //permite o fluxo dos dados.

  for (int x = 7; x >=0; x--) {
    digitalWrite(CLOCK, LOW); //pronto para receber o bit.

    if (dado[x])digitalWrite(DATA, HIGH); //Grava o bit como 1
    else  digitalWrite(DATA, LOW); //Grava o bit como 0

    digitalWrite(CLOCK, HIGH); //grava o bit recebido.
  }
  digitalWrite(LATCH, HIGH); //finaliza o fluxo dos dados e envia os 8 bits.


}

