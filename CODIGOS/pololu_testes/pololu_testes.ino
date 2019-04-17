
void setup() {
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {

  voltas(2,1);
  delay(1000);
  voltas(2,0);
  delay(1000);
}

void centimetros(float cm, boolean dir){
  digitalWrite(12,dir);
  float fuso = 5; //5mm de fuso 
  int passos = ((cm/0.10000)*200)/fuso; // regra de tres para saber a quantidade de passos necessarios
  for (int i = 1;i<=passos;i++){
    digitalWrite(13,1);
    digitalWrite(13,0);
    delay(2);
  }
}

void voltas(float volt, boolean dir){

  digitalWrite(12,dir);
  int  passos = volt*200;
  for (int i = 1;i<=passos;i++){
    digitalWrite(13,1);
    digitalWrite(13,0);
    delay(2);
  }

}


