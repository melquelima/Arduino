int ledPin = 9;
int numero = -5;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop(){
  if (Serial.available() > 0){
   numero=Serial.read(); 
  }
  if (numero > 0){
    if (numero =='1'){
   digitalWrite(ledPin,HIGH); 
   delay(2000);
    }
     if (numero =='0'){
   digitalWrite(ledPin,LOW); 
   delay(2000);
    }
  }
  numero=-5;
}
