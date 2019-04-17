int a = 11;
int b = A1;
int c = A4;
int led = A5;

void setup() {
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(led,OUTPUT);
digitalWrite(led,0);
  Serial.begin(9600);
  Serial.println("OK");
}

void loop() {

  if(Serial.available()>0){
    int comando = Serial.read();
    switch(comando){
    case 'a':
      digitalWrite(a,1);
      delay(2000);
      digitalWrite(a,0);
      delay(2000);  
      break; 
    case 'b':
      digitalWrite(b,1);
      delay(2000);
      digitalWrite(b,0);
      delay(2000);  
      break;
    case 'c':
      digitalWrite(c,1);
      delay(2000);
      digitalWrite(c,0);
      delay(2000);  
      break;
    }
    Serial.println(comando);
  }


}




