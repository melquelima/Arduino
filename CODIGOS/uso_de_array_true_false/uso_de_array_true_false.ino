boolean state[] = {false, false, false};

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("primeira variável é: ");
  Serial.println(state[0]);
  state[0] = true;
  Serial.print("primeira variável mudou para: ");
  Serial.println(state[0]);
  delay(1000);
  Serial.print("segunda variável é: ");
  Serial.println(state[1]);
  state[1] = true;
  Serial.print("segunda variável mudou para: ");
  Serial.println(state[1]);
  delay(1000);
  Serial.print("terceira variável é: ");
  Serial.println(state[2]);
  state[2] = true;
  Serial.print("terceira variável mudou para: ");
  Serial.println(state[2]);
  delay(1000);
  state[0] =! state[1]; 
  state[1] =! state[2]; 
  state[2] =! state[3];
  delay(1000);
  Serial.print("primeira variável voltou para: ");
  Serial.println(state[0]);
  Serial.print("segunda variável voltou para: ");
  Serial.println(state[1]);
  Serial.print("terceira variável voltou para: ");
  Serial.println(state[2]);
  delay(2000);
}
