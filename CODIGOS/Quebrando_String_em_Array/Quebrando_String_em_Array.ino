int const clock = 2; 
int const latch = 1; 
int const data  = 0; 

int array[8]={0,0,0,0,0,0,0,0};


void setup() {
Serial.begin(9600);
}

void loop() {
 comando("10110101");
 reset();
 toogle(5);
}

void comando(char* str){
for(int i = 0; i<=7; i++){
  array[i] = str[i]-48;
}
  execute();
}


void execute(){
 digitalWrite(latch,LOW);
     for (int x = 0; x <= 7; x++) {
      digitalWrite(clock,LOW);
      
      if (array[x]) {
        digitalWrite(data,HIGH);
      } else {
        digitalWrite(data,LOW);
      }
      
      digitalWrite(clock,HIGH);
    }    
    
    digitalWrite(latch,HIGH);
  
  
}


void reset(){
 for(int i = 0; i<=7; i++)
 array[i] = 0;
 execute();
}

void toogle(int comando){
  array[comando-1] = !array[comando-1];
  execute();
}

void sequencia(int direc, int tempo){
  reset();
  
  if (direct){
  for(int i =0 i<=7;i++){
   toogle(i);
   delay(tempo);
    toogle(i); 
    }
  }else{
    for(int i =7; i<=0;i--){
   toogle(i);
   delay(tempo);
    toogle(i); 
  }
  
}


