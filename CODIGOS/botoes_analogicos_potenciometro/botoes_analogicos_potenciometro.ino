void setup() {
Serial.begin(9600);
pinMode(A5,INPUT);
pinMode(A4,INPUT);
}

void loop() {
int pressionado = get_bot();

switch(pressionado){
 case 1:
 Serial.println("botao 1");
 while(pressionado == 1){
 pressionado = get_bot();  
}
break;

case 2:
 Serial.println("botao 2");
 while(pressionado == 2){
 pressionado = get_bot(); 
 }
break;

case 3:
 Serial.println("botao 3");
 while(pressionado == 3){
  pressionado = get_bot(); 
 }
break;

case 4:
 Serial.println("botao 4");
 while(pressionado == 4){
 pressionado = get_bot(); 
 }
break;
}
}


int get_bot(){
   if(botao() != 0){
  return botao();
  delay(50);
 }
  if(botao2() != 0){
  return botao2();
  delay(50);
 }
  return 0;
}


int botao(){
  int comando = analogRead(A5);
  if(comando >=100 && comando <=200){return 1;}
  if(comando >=600 && comando <=900){return 2;}
  return 0;  
}

int botao2(){
  int comando2 = analogRead(A4);
  if(comando2 >=100 && comando2 <=200){return 3;}
  if(comando2 >=600 && comando2 <=900){return 4;}
  return 0;
}
