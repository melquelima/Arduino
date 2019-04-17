#include <TimerOne.h>

int seg[7] = {11,12,A1,A0,13,10,9};
int dig[3] = {2,3,4};
int numero[3] = {1,1,1};
int atual = 0;
int pot = A4;
int aux_seg = 0;
int range[10][2]={{0,40},{62,142},{164,244},{266,346},{328,448},{470,550},{572,652},{674,754},{776,856},{878,958}};

//-----------------------------

int aux[10][7]={
 {1,1,1,1,1,1,0},
 {0,1,1,0,0,0,0},
 {1,1,0,1,1,0,1},
 {1,1,1,1,0,0,1},
 {0,1,1,0,0,1,1},
 {1,0,1,1,0,1,1},
 {1,0,1,1,1,1,1},
 {1,1,1,0,0,0,0},
 {1,1,1,1,1,1,1},
 {1,1,1,0,0,1,1}, 
};
//---------------------------------


void setup(){
  pinMode(pot,INPUT);
  for(int i = 0;i<7;i++){
    pinMode(seg[i],OUTPUT);
    pinMode(dig[i],OUTPUT);
  }
Serial.begin(9600);
  Timer1.initialize(900);
  Timer1.attachInterrupt( _display2 );
}

void loop(){
  /*int h=0;
  int valor = analogRead(pot);

 for(int j=0;j<10;j++){
   numero[h] = valor>=range[j][0] && valor<=range[j][1]?j:numero[h];
 }

 Serial.println(numero[h]);
 */
}

void _display2(){
  apaga();
  digitalWrite(dig[0],0);
  digitalWrite(dig[1],0);
  digitalWrite(dig[2],0);

  digitalWrite(dig[atual],1);
  digitalWrite(seg[aux_seg],!aux[numero[atual]][aux_seg]);
  aux_seg ++;
  atual = aux_seg==8? atual+1:atual;
  atual = atual==3?0:atual;
  aux_seg = aux_seg==8?0:aux_seg;
}


void apaga(){
  for(int i = 0;i<7;i++){
    digitalWrite(seg[i],1);
  } 
}




