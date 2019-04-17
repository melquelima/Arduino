int pistola = 13;
  int in_esquerda = 4;
  int in_direita = 5;
  
void setup(){
  pinMode(pistola,OUTPUT);
  pinMode(in_esquerda,INPUT_PULLUP);
  pinMode(in_direita,INPUT_PULLUP);
  pinMode(14,INPUT);
  pinMode(15,INPUT);
  Serial.begin(9600);  
}
//!digitalRead(in_esquerda)
void loop(){
    //while(1){Serial.print("status: ");Serial.println(saii());}  
  while(!digitalRead(in_esquerda)&& !saii()){
    if(!ler_esquerda()){
      digitalWrite(pistola,0);
      Serial.println("1");
      while(ler_direita()&& !saii()){}
      Serial.println("2");
      while(!ler_direita()&& !saii()){}
      Serial.println("3");
    }
     Serial.println("4");
    digitalWrite(pistola,1);
  }
  while(!digitalRead(in_direita) && saii()){
    if(ler_direita()){
      digitalWrite(pistola,0);
      while(!ler_esquerda() && !saii()){}
      while(ler_esquerda() && !saii()){}
      digitalWrite(pistola,1);
    }
  }
 while(digitalRead(in_direita) && digitalRead(in_esquerda)){} 
  digitalWrite(pistola,0);
  Serial.println("..");
 }

boolean saii(){
  if (digitalRead(in_direita) && digitalRead(in_esquerda))
 return true;
 return false;
}
boolean ler_esquerda(){
 for(int i = 0;i<=20;i++){
  if(digitalRead(15)){return false;}
  delay(20);
 } 
  return true;
}

boolean ler_direita(){
 for(int i = 0;i<=20;i++){
  if(digitalRead(14)){return false;}
  delay(20);
 } 
  return true;
}

