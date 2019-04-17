
int relogio[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  for (int i=2; i<=7;i++)
  pinMode(i,OUTPUT);
 
}

void loop() {
  
  executa();
}

void executa(){
  digitalWrite(2,LOW);
  neutros(1);
  for(int i =0; i<=5;i++)
  {
    digitalWrite(3,LOW);
    
    if(relogio[i]){digitalWrite(4,HIGH);}
    else{digitalWrite(4,LOW);}   
    
    digitalWrite(3,HIGH);
  }
  digitalWrite(2,HIGH); 
  
  digitalWrite(5,LOW); 
  neutros(0);
  
  for(int i =6; i<=12;i++)
  {
    digitalWrite(6,LOW);
    
    if(relogio[i]){digitalWrite(7,HIGH);}
    else{digitalWrite(7,LOW);}   
    
    digitalWrite(6,HIGH);
  }
  
 digitalWrite(5,HIGH); 
}



void neutros(boolean x){
  if(x){
    for(int i =0; i<=1;i++){
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);   
  digitalWrite(3,HIGH);
    }
    return;
  }
   digitalWrite(6,LOW);
  digitalWrite(7,LOW);   
  digitalWrite(6,HIGH);
  
}


void um(char d){
  switch(d){
    case 'h': // primeiro digito da hora
      relogio[0] = 0;
      relogio[1] = 1;
    break;
    case 'o': //segundo digito da hora
      relogio[2] = 0;
      relogio[3] = 0;
      relogio[4] = 0;
      relogio[6] = 1;
    break;
    case 'r': //primeiro digito do minuto
      relogio[7] = 0;
      relogio[8] = 0;
      relogio[9] = 1;
    break;
    case 'a': //segundo digito do minuto
      relogio[10] = 0;
      relogio[11] = 0;
      relogio[12] = 0;
      relogio[13] = 1;
    break;
  }
}
