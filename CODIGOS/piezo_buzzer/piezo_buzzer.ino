int piezo = 7; 
int  buzzer= 13;

void setup(){
  pinMode(piezo, INPUT);
  pinMode(buzzer,OUTPUT); 
} 
void loop(){ 
  if(digitalRead(piezo) == HIGH){
      digitalWrite(buzzer, HIGH);   delay(50);}
else{
       digitalWrite(buzzer, LOW); 
 
}
}
