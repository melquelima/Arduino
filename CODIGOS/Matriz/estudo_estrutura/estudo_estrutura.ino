typedef struct {
 int frames;
 int* matriz;
}efeito;

#include <mills.h>

mills tempo(100);

#define    clk     8
#define    latch   9
#define    data    10
#define    NUM_EF  2

int pinBotao = 11;
int efeito_atual = 0;
int frame = 0;

int ef1[2][3] = {
  {B11110000, B11111001, B10011111},
  {B11110000, B00000110, B01100000}
};

int ef2[1][3] = {
  {B11111111, B11111111, B11110000}
};

efeito _ef1 = {2,(int*) ef1};
efeito _ef2 = {1,(int*) ef2};

efeito* efeitos[NUM_EF]={&_ef1,&_ef2};

void setup() {
  Serial.begin(9600);
  pinMode(clk,   OUTPUT);
  pinMode(data,  OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(pinBotao, INPUT);
  tempo.on(); //inicia a contagem
}

void loop() {
  
   if(tempo.verifica()){
    int n_frames = (*(efeitos[efeito_atual])).frames;
    run_efect_frame(efeito_atual,frame);
    frame = (frame==(n_frames-1)?0:frame+1);
    tempo.reset();//reinicia a contagem
  }
  
   if(digitalRead(pinBotao)){
   efeito_atual = (efeito_atual==(NUM_EF-1)?0:1);
   frame = 0;
   while(digitalRead(pinBotao)){};
    delay(200);
  }
  
}

void run_efect_frame(int ef,int frame)
{
  digitalWrite(latch,  LOW);
  for (int col = 0; col < 3; col++){
    int data2 = (*((*(efeitos[ef])).matriz + frame*3 + col);
    shiftOut(data, clk, MSBFIRST, data2);
  }  
  digitalWrite(latch, HIGH);
}



