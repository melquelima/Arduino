void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
Serial.println(floor(log10(abs(10230))) + 1);
delay(500);
}
