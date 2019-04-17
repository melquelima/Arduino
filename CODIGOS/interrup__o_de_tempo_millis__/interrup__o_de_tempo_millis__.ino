int led = 13;

//-----------variaves millis------------
unsigned long tempo_anterior = 0;
unsigned long tempo_espera = 5000;
//-----------fim de variaveis-----------

void setup()
{
pinMode(led,OUTPUT);
Serial.begin(9600);
}

void loop()
{
if(Serial.available())
{
int n = Serial.read();
if(n == 'a'){ // acende ou apaga o led// ou tabem desliga o temporizador
digitalWrite(led,!digitalRead(led)); // acende ou apaga o led
tempo_anterior = 0; // desativa a contagem
n =0;
}

if(n == 'b'){
  digitalWrite(led,HIGH); // acende o led 
  tempo_anterior = millis(); // inicia a contagem
  n = 0;  
}
}
tempo(); // verifica o tempo passado e se esta ativada a cotnagem
}

void tempo(){
  if(tempo_anterior != 0){ // se a contagem estiver ativada
  if ((millis() - tempo_anterior) >= tempo_espera){ // se o momento atual for maior que 5s
    digitalWrite(led,0); // apague o led
    tempo_anterior = 0; // desative a contagem
    return;
  }
  digitalWrite(led,1); // se o momento atual for menor que 5s mantenha o led aceso
}
  
}

