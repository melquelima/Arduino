#include <mills.h>
mills tempo(500); // declara o tempo a ser estabelecido
mills tempo2(2000);

typedef struct {
 int n_frames;
 int* frames;
}animation;

//========================================================================================================
// --- Mapeamento de Hardware ---
#define    clk     8
#define    latch   9
#define    data    10
 
#define N_EFEITOS  3 
// ========================================================================================================
// --- Variaveis Globais---
int pinBotao =  11;
int frame    =   0;
int efeito   =   0;
boolean autom = false;

int efeito1[4][2] = {   
  {B01000000, B00000010},
  {B00100000, B00000100},
  {B00010000, B00001000},
  {B00001000, B00010000},
};
int efeito2[3][2] = {   
  {B11111111, B11110000},
  {B11111111, B11100000},
  {B11111111, B11010000},
};
int abajur[1][2] = {   
  {B11111111, B11110000}
};

animation _efaba = {1,(int*) abajur};
animation _ef1 = {4,(int*) efeito1};
animation _ef2 = {3,(int*) efeito2};

animation* efeitos[N_EFEITOS]={&_efaba,&_ef1,&_ef2};

// ========================================================================================================
// --- Configurações Iniciais ---
void setup() {
  Serial.begin(9600);
  pinMode(     clk,   OUTPUT);
  pinMode(    data,   OUTPUT);
  pinMode(   latch,   OUTPUT);
  pinMode(pinBotao,    INPUT);
  tempo.on(); //inicia a contagem
  //Serial.println((*efeitos[0]).n_frames);
  
} //end setup

// ========================================================================================================
// --- Loop Infinito ---
void loop() {
  if(tempo.verifica()){AtualizaFrame();tempo.reset();}
  if(tempo2.verifica()){efeito = (efeito == N_EFEITOS -1?0:efeito+1);frame=0;tempo2.reset();}
  
  if(digitalRead(pinBotao)){
    autom = !autom;
   if(autom){
     tempo2.on();
     tempo2.reset();
   }else{
     tempo2.off();
     efeito =0;
     AtualizaFrame();
   }
   frame = 0;
   
   while(digitalRead(pinBotao)){};
    delay(200); 
  }
} 

void AtualizaFrame(){
  int n_frames = (*(efeitos[efeito])).n_frames;
   frame = (frame==n_frames-1?0:frame+1);
   int _B1 = *((*efeitos[efeito]).frames + arrAddr(frame,0));
   int _B2 = *((*efeitos[efeito]).frames + arrAddr(frame,1));
   envia(_B1,_B2);
}
// ========================================================================================================

int arrAddr(int l,int c){
 return (l*2) + c;
}

void envia(int _B1,int _B2){
  digitalWrite(latch, LOW);
  shiftOut(data, clk, MSBFIRST, _B1);
  shiftOut(data, clk, MSBFIRST, _B2);
  digitalWrite(latch, HIGH); 
  
  Serial.print(frame);
  Serial.print(" - ");
  Serial.print(_B1,BIN);
  Serial.print(" - ");
  Serial.println(_B2,BIN);
}
