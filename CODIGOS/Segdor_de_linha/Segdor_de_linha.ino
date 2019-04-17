int led = 13;
int botao = 12;

void setup() {
pinMode(led,OUTPUT);
pinMode(botao,INPUT);
}

void loop() {

  if(digitalRead(botao)){
    digitalWrite(led,!digitalRead(led));
    delay(100);
  }
  
}
