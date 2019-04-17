long tempo = 0;
int dig = 1; 
int portas[4] = {0,1,2,4};
int um[4]={0,0,1,0};
int dois[4]={0,0,0,1};
int tres[4]={0,0,1,1};
int quatro[4]={0,1,0,1};
int cinco[4]={0,1,1,1};
int seis[4]={1,1,0,1};
// the setup routine runs once when you press reset:
void setup() {                
for(int i = 0; i < 5; i++)
pinMode(portas[i], OUTPUT);
pinMode(3,INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {

dig = (dig == 6 ? 1: dig+1);
int bot = digitalRead(3);
if(bot){numero();}

}


void numero(){
  apagaTudo();
    for(int i = 0; i < 4; i++)
  {
    if(dig == 1){
       if(um[i]){digitalWrite(portas[i], HIGH);}  
    }
        if(dig == 2){
       if(dois[i]){digitalWrite(portas[i], HIGH);}  
    }
        if(dig == 3){
       if(tres[i]){digitalWrite(portas[i], HIGH);}  
    }
     if(dig == 4){
       if(quatro[i]){digitalWrite(portas[i], HIGH);}  
    }
     if(dig == 5){
       if(cinco[i]){digitalWrite(portas[i], HIGH);}  
    }
     if(dig == 6){
       if(seis[i]){digitalWrite(portas[i], HIGH);}  
    }

  }
  delay(10);
 }

void apagaTudo(){
    for(int i = 0; i < 4; i++)
  {
   digitalWrite(portas[i],LOW);  
  }
  
}
