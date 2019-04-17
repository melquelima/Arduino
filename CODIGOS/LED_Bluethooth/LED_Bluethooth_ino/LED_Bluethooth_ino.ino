int valor;
void setup(){
pinMode(13,OUTPUT); 
Serial.begin(9600);
}
void loop(){
if(Serial.available()>0){
valor = Serial.read();
}
if (valor == '1'){
digitalWrite(13,HIGH); 
}
else if (valor == '2'){
digitalWrite(13,LOW); 
}
else if (valor == '3'){
digitalWrite(13,HIGH); 
delay(200);
digitalWrite(13,LOW);
delay(200);
}
}
