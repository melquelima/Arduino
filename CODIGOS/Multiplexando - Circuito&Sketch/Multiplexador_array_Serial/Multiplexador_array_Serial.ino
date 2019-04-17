int A = 8;
int B = 9;
int C = 10;

int leds[6] = {0,0,0,0,0,0};

void setup() {
apagaTudo();
}

void loop() {
  for(int i = 0; i<6;i++){
    if(leds[i]){led(i);}
  }
  
if(Serial.available()){
int comando = Serial.read(); 
 leds[comando-49] = !leds[comando-49];
}
  
}

void led(int x){
  switch(x){
  case 0:
  setar(A,B);
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  break;
  
  case 1:
  setar(A,B);
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  break;
  
    case 2:
  setar(B,C);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  break;
  
    case 3:
  setar(B,C);
  digitalWrite(B,HIGH);
  digitalWrite(C,LOW);
  break;
  
    case 4:
  setar(A,C);
  digitalWrite(A,LOW);
  digitalWrite(C,HIGH);
  break;
  
    case 5:
  setar(A,C);
  digitalWrite(A,HIGH);
  digitalWrite(C,LOW);
  break;
  }
   delay(1);
   apagaTudo();
}

void apagaTudo(){
 pinMode(A,INPUT); 
 pinMode(B,INPUT);
 pinMode(C,INPUT); 
}

void setar (int w, int z){
 pinMode(w,OUTPUT); 
 pinMode(z,OUTPUT);
  
}
