const int FRAMES_ANIMACAO = 54;
const int VELOCIDADE = 120; //ms
const int N_LINHAS = 5;
const int N_COLUNAS = 8;
 
int lin[N_LINHAS] = {2,3,4,5,6};
 
int const clock = 8; //pino do arduino ligado ao clock do 74HC595
int const latch = 9; //pino do arduino ligado ao latch do 74HC595
int const data  = 10; //pino do arduino ligado ao data do 74HC595

 
int leds[N_LINHAS][FRAMES_ANIMACAO] = {
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
 
int k = 0;
long proximo = VELOCIDADE;
void setup() {
 for(int i = 0; i < N_LINHAS; i++)
 pinMode(lin[i], OUTPUT);
 
 pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(data,OUTPUT);
 
 apagartudo();
}
 
void apagartudo() {
int i;
for(i = 0; i < N_LINHAS; i++)
digitalWrite (lin[i], LOW);

digitalWrite(latch,LOW); //permite o fluxo dos dados.
  for (int x = 0; x <= 7; x++) {
      digitalWrite(clock,LOW); //pronto para receber o bit.
      digitalWrite(data,HIGH);
     digitalWrite(clock,HIGH); //grava o bit recebido.
  }
  digitalWrite(latch,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.  
}
 
void loop()
{
 for(int i = 0; i < N_LINHAS; i++) {
 for(int j = 0; j < N_COLUNAS; j++) {

 apagartudo();
 if(leds[i][j+k]) {
 
   digitalWrite(lin[i], HIGH);
 shifter(j);
 } 
 delayMicroseconds(250);
 }
 }
  if(millis() >= proximo) {
 proximo = millis() + VELOCIDADE;
 k = (k >= FRAMES_ANIMACAO-N_COLUNAS ? 0 : k+1);
 }

}





void shifter(int n){
  int num;
  switch(n){
    case 0:num = 1;break;case 1:num = 2;break;case 2:num = 4;break;case 3:num = 8;break;case 4:
    num = 16;break;case 5:num = 32;break;case 6:num = 64;break;case 7:num = 128;break;
    }
  
  digitalWrite(latch,LOW); //permite o fluxo dos dados.
  for (int x = 0; x <= 7; x++) {
      digitalWrite(clock,LOW); //pronto para receber o bit.
      
      if (num & (1 << x)) {
        digitalWrite(data,LOW);
      } else {
        digitalWrite(data,HIGH);
      }
      
      digitalWrite(clock,HIGH); //grava o bit recebido.
    }    
    
    digitalWrite(latch,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.  
}

