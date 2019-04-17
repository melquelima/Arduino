const int N_LINHAS = 5;
const int N_COLUNAS = 8;

int const clock_linha = 7; //pino do arduino ligado ao clock do 74HC595
int const latch_linha = 6; //pino do arduino ligado ao latch do 74HC595
int const data_linha  = 5; //pino do arduino ligado ao data do 74HC595

int const clock_coluna = 8; //pino do arduino ligado ao clock do 74HC595
int const latch_coluna = 9; //pino do arduino ligado ao latch do 74HC595
int const data_coluna  = 10; //pino do arduino ligado ao data do 74HC595


//int col[N_COLUNAS] = {7,8,9,10,11,12,13,14};

int leds[N_LINHAS] [N_COLUNAS] = { 
{0,0,1,0,0,1,0,0}, // faça seu desenho aki
{0,1,1,1,1,1,1,0},
{0,1,1,1,1,1,1,0},
{0,0,1,1,1,1,0,0},
{0,0,0,1,1,0,0,0}
};

int i, j;
void setup() {
  pinMode(clock_linha,OUTPUT);
  pinMode(latch_linha,OUTPUT);
  pinMode(data_linha,OUTPUT);


  pinMode(clock_coluna,OUTPUT);
  pinMode(latch_coluna,OUTPUT);
  pinMode(data_coluna,OUTPUT);

apagartudo();
}


void loop()
{
for (i = 0; i < N_LINHAS; i++) {
for (j = 0; j <N_COLUNAS; j++) {
  apagartudo();
if (leds[i][j] ) {
  linha(i);
  coluna(j);
}
delayMicroseconds(200);
}
}
}





void apagartudo() {

  digitalWrite(latch_linha,LOW); //permite o fluxo dos dados.
  for (int x = 0; x <= 7; x++) {
      digitalWrite(clock_linha,LOW); //pronto para receber o bit.
      digitalWrite(data_linha,LOW);
     digitalWrite(clock_linha,HIGH); //grava o bit recebido.
  }
  digitalWrite(latch_linha,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.  
  
  
digitalWrite(latch_coluna,LOW); //permite o fluxo dos dados.
  for (int x = 0; x <= 7; x++) {
      digitalWrite(clock_coluna,LOW); //pronto para receber o bit.
      digitalWrite(data_coluna,HIGH);
     digitalWrite(clock_coluna,HIGH); //grava o bit recebido.
  }
  digitalWrite(latch_coluna,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.  
}


void coluna(int n){
  int num;
  switch(n){
    case 0:num = 1;break;
    case 1:num = 2;break;
    case 2:num = 4;break;
    case 3:num = 8;break;
    case 4:num = 16;break;
    case 5:num = 32;break;
    case 6:num = 64;break;
    case 7:num = 128;break;
    }
  
  digitalWrite(latch_coluna,LOW); //permite o fluxo dos dados.
  for (int x = 0; x <= 7; x++) {
      digitalWrite(clock_coluna,LOW); //pronto para receber o bit.
      
      if (num & (1 << x)) {
        digitalWrite(data_coluna,LOW);
      } else {
        digitalWrite(data_coluna,HIGH);
      }
      
      digitalWrite(clock_coluna,HIGH); //grava o bit recebido.
    }    
    
    digitalWrite(latch_coluna,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.  
}

void linha(int k){
  int num=-5;
  switch(k){
    case 0:num = 1;break;
    case 1:num = 2;break;
    case 2:num = 4;break;
    case 3:num = 8;break;
    case 4:num = 16;break;
    case 5:num = 32;break;
    case 6:num = 64;break;
    case 7:num = 128;break;
    }
  
  digitalWrite(latch_linha,LOW); //permite o fluxo dos dados.
  for (int x = 0; x <= 7; x++) {
      digitalWrite(clock_linha,LOW); //pronto para receber o bit.
      
      if (num & (1 << x)) {
        digitalWrite(data_linha,HIGH);
      } else {
        digitalWrite(data_linha,LOW);
      }
      
      digitalWrite(clock_linha,HIGH); //grava o bit recebido.
    }    
    
    digitalWrite(latch_linha,HIGH); //finaliza o fluxo dos dados e envia os 8 bits.  
}


