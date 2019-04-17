int ledPins[] = { 12, 11, 10, 9, 8, 7 }; // Array que determina quantos leds serao usados e quais pinos estao
int rele = 13;                           // determina o pino 13 como rele
 
void setup() {
  for (int leds = 0; leds < 6; leds++)  {     // loop que seta as portas dos leds de 12 à 7 como OUTPUTs
    pinMode(ledPins[leds], OUTPUT);      
  }
  pinMode(rele,OUTPUT);                   // determina a porta rele (13) como OUTPUT
}

void loop() {
digitalWrite(rele,LOW);                            //liga o rele
for (int i=0;i<6;i++){ if (i==0){delay(5000);}     //loop que conta de 0 a 5 acendendo os 6 leds por sequencia  OBS: 0,1,2,3,4,5 sao 6 leds
 digitalWrite(ledPins[i],HIGH);
delay(5000);                                       //espera 5 segundos
}
digitalWrite(rele,HIGH);                           //desliga o rele
for (int i=5;i>=0;i--){ if (i==6){delay(5000);}    //loop que conta de 5 a 0 apagando os 6 leds por sequencia
 digitalWrite(ledPins[i],LOW);
delay(5000);                               
}
  
}

