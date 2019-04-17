int lm35 = 0;
int valorLido = 0;
float temperatura = 0;

void setup(){
Serial.begin(9600); 
}

void loop(){
valorLido = analogRead(lm35);
temperatura = (valorLido * 0.00488);
temperatura  = temperatura *100;
Serial.println(temperatura);
delay(1000);
}
