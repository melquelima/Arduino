int bot = 6;
int quantidade = 0;
long anterior = 0;
long tempo = 5000;


void setup() {
Serial.begin(9600);
pinMode(bot,INPUT_PULLUP);
}

void loop() {
  boolean estado = digitalRead(bot);
  

  if(estado){
  quantidade = quantidade + 1;
  Serial.println("pressionado");
  delay(50);
  }
  
  
if(millis() - anterior >= tempo ) {
anterior = millis();
Serial.print("botao pressionado ");
Serial.print(quantidade);
Serial.println(" vezes");
quantidade = 0;
 }
  
}
