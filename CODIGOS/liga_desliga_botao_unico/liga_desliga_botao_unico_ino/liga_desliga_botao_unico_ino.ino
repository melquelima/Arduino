
int Led = 13;
int botao = 7;
boolean set = false;
void setup() {
pinMode(Led,OUTPUT);
pinMode(botao,INPUT_PULLUP);
}

void loop() {
  
  if (!digitalRead(botao)){ // se botao pressionado
 set = (!set?true:false); // muda o valor de set 
  digitalWrite(Led,set); // troca o valor do led
  while(!digitalRead(botao)){} // espera tirar o dedo do botao para coninuar o loop
 }
}
