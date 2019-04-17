int sensore = 10;
int sensord = 11;
int H_e = 12;
int H_d = 13;
int H2_e = 9;
int H2_d = 8;


void setup()
{
Serial.begin(9600);
pinMode(sensore, INPUT);
pinMode(sensord, INPUT);
pinMode(H_e, OUTPUT);
pinMode(H_d, OUTPUT);
pinMode(H2_e, OUTPUT);
pinMode(H2_d, OUTPUT);
}

void loop()
{

if(!digitalRead(sensore)&&!digitalRead(sensord))
{
digitalWrite(H_e,HIGH); //ir pra frente
digitalWrite(H_d,LOW);  // ||    ||
digitalWrite(H2_e,HIGH); //ir pra frente
digitalWrite(H2_d,LOW);  // ||    ||
}

if(digitalRead(sensore)&&!digitalRead(sensord)){
digitalWrite(H_e,HIGH); //ir pra frente
digitalWrite(H_d,LOW);  // ||    ||

digitalWrite(H2_e,LOW); //ir pra traz
digitalWrite(H2_d,HIGH);  // ||    ||


}
if(!digitalRead(sensore)&&digitalRead(sensord)){

digitalWrite(H2_e,HIGH); //ir pra frente
digitalWrite(H2_d,LOW);  // ||    ||

digitalWrite(H_e,LOW); //ir pra traz
digitalWrite(H_d,HIGH);  // ||    ||
  
}
}
