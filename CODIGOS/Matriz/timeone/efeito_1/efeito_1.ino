#include <TimerOne.h>

int linhas[4] = {3,4,5,6};
int colunas[4] = {7,8,9,10};
int l=0,c= 0;

int matriz[4][4]={
 {0,0,0,0}, 
 {0,0,0,0},
 {0,0,0,0},
 {0,0,0,0},
};

int matrix[2]={0x01,0x01};


void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i<4;i++){
    pinMode(linhas[i],OUTPUT);
    pinMode(colunas[i],OUTPUT); 
  }
  Timer1.initialize(1000);
  Timer1.attachInterrupt( timerIsr );
apaga_tudo();

digitalWrite(linhas[0],0);
digitalWrite(colunas[0],1);

}

void loop() {

  
  for(int i = 3;i>=0;i--){
    matriz[0][i]= !matriz[0][i];
    delay(100);
  }
  
  for(int i = 1 ;i<4;i++){
   matriz[i][0]= !matriz[i][0];
    delay(100);
  }
  
  for(int i = 1 ;i<4;i++){
    matriz[3][i]= !matriz[3][i];
    delay(100);
  }
  
  

  for(int i = 2;i>=1;i--){
    matriz[i][3]= !matriz[i][3];
    delay(100);
  }
  
  
  delay(1000);
  
  for(int i = 0;i<4;i++){
  for(int j = 0;j<4;j++){
     matriz[i][j] = !matriz[i][j];
    delay(100);
  }
  
}

  delay(1000);  
}



void timerIsr(){
  apaga_tudo();
  
   if(matriz[l][c]){
         digitalWrite(linhas[l],0);
         digitalWrite(colunas[c],1);
       }
       
  l = (l==3?0:l+1);
  c = (l==3?c+1:c);
  c = (c==4?0:c);
  
    
}

void apaga_tudo(){
  for(int i = 0;i<4;i++){
    digitalWrite(colunas[i],0);
    digitalWrite(linhas[i],1);
  } 
}


