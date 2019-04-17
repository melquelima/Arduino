int motor = 3;
int botUp = 6;
int botDown = 7;
int pwm = 0;


void setup() {
 pinMode(motor,OUTPUT);
 pinMode(botUp,INPUT_PULLUP);
 pinMode(botDown,INPUT_PULLUP);
}

void loop() {
  
  int state_1 = digitalRead(botUp);
  int state_2 = digitalRead(botDown);
  if(state_1 == HIGH && pwm <300)pwm += 50;
  if(state_2 == HIGH && pwm >0)pwm -= 50;
  analogWrite(motor,pwm);
  delay(50);
 
}
