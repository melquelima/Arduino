int bot = 4;
int led = 13;
int luz = 6;
int pot = A0;
int comando = 0;
int Pwm = 0;
unsigned long anterior = 0;


void setup(){
  pinMode(bot,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  pinMode(luz,OUTPUT); 
   pinMode(pot,INPUT); 
  Serial.begin(9600);
  
}
void loop(){
  
  int ler = digitalRead(bot);
  if(ler == HIGH){
      comando = (comando < 2? comando+1: 0 );
   delay(150);
   while(ler == HIGH){ler = digitalRead(bot);}
  }
  
  int valor = analogRead(pot)/4;
  Pwm = valor;
  
 switch(comando){
  case 0:
  digitalWrite(luz,LOW);
  break;
  case 1:
  analogWrite(luz,Pwm);
  break;
  case 2: 
   sleep();
  break;
 }
}

void sleep(){
  
  digitalWrite(led,HIGH);
  analogWrite(luz,Pwm);
  
  anterior = (anterior ==0? millis() : anterior = anterior);
  
  
  if((millis() - anterior) >= 5000){
  anterior = 0;
   digitalWrite(led,LOW);
   digitalWrite(luz,LOW);
   comando = 0;
  }
}


