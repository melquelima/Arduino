int A = 13;
int B = 12;
int C = 11;
int D = 10;
int Enable = 9;
int bites[4]={0,0,0,0};
int Dec = 0;

void setup(){
  pinMode(A,INPUT);
  pinMode(B,INPUT);
  pinMode(C,INPUT);
  pinMode(D,INPUT);
  pinMode(Enable,INPUT);
  Serial.begin(9600);
}


void loop(){

  int tecla = gettec();
if(tecla != 99){
Serial.println(tecla);
delay(100);
}  
 
}

int gettec(){

 if(digitalRead(Enable)){
bites[0] = digitalRead(A);
bites[1] = digitalRead(B);
bites[2] = digitalRead(C);
bites[3] = digitalRead(D);
 Dec = 0;
 Dec += (bites[0]?1:0);
 Dec += (bites[1]?2:0);
 Dec += (bites[2]?4:0);
 Dec += (bites[3]?8:0);
 return Dec; 
 }
 else 
 return 99;
  
}
