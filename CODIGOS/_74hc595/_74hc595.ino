int const clock = 2; //pino do arduino ligado ao clock do 74HC595
int const latch = 3; //pino do arduino ligado ao latch do 74HC595
int const data  = 4; //pino do arduino ligado ao data do 74HC595

void setup() {
  //definindo os pinos como de saída
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(data,OUTPUT);
}

void loop() {
  //Contando de 0 até 255
  for (int i = 0; i <= 255; i++) {
    digitalWrite(latch,LOW); //permite o fluxo dos dados.
       
    for (int x = 0; x <= 7; x++) {
      digitalWrite(clock,LOW); //pronto para receber o bit.
      
      if (i & (1 << x)) {
        digitalWrite(data,HIGH);
      } else {
        digitalWrite(data,LOW);
      }
      
      digitalWrite(clock,HIGH); //grava o bit recebido.
    }    
    
    digitalWrite(latch,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.
    
    delay(100); //tempo de espera entre a exibição de um número e o outro.
  }
}
