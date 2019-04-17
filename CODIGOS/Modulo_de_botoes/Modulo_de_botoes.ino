int bot =A5;

void setup() {
Serial.begin(9600);
pinMode(bot,INPUT);

}

void loop() {
  int variavel;
  
  do{
   variavel=analogRead(bot); 
  }while(variavel<200);
  
  Serial.println(variavel);
  Serial.println(retornaBot(variavel));
  delay(400);
}

String retornaBot(int x){
  if(x>=200 && x<=210)
  return "Botão 1 apertado";
  
   else if(x>=400 && x<=410)
  return "Botão 2 apertado";
  
   else if(x>=600 && x<=615)
  return "Botão 3 apertado";
  
   else if(x>=800 && x<=830)
  return "Botão 4 apertado";
}
