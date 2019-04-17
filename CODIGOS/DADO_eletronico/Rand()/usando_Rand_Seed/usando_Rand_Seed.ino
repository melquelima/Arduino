void setup(){
Serial.begin(9600); 

}

void loop(){
  int aleatorio;
 srand(millis());
  for (int i = 0; i < 10; i++){
  do{ aleatorio = rand()%7;}while(aleatorio == 0);
Serial.print(aleatorio);
}
Serial.println();
  delay(1000);
}
