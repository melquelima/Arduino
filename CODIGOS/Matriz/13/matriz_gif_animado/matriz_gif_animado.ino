const int N_LINHAS = 5;
const int N_COLUNAS = 8;
long tempo = 0;
int lin[N_LINHAS] = {2,3,4,5,6};
int col[N_COLUNAS] = {7,8,9,10,11,12,13,14};
int leds[N_LINHAS] [N_COLUNAS] = { 
{0,1,1,0,0,1,1,0},
{0,1,1,0,0,1,1,0},
{1,0,0,0,0,0,0,1},
{0,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0}
};

int leds2[N_LINHAS] [N_COLUNAS] = { 
{0,1,1,0,0,1,1,0},
{0,1,1,0,0,1,1,0},
{0,0,0,1,1,0,0,0},
{0,0,1,0,0,1,0,0},
{0,0,1,0,0,1,0,0}
};

int leds3[N_LINHAS] [N_COLUNAS] = { 
{0,1,1,0,1,1,1,0},
{0,1,1,0,1,0,0,1},
{0,0,0,0,1,1,1,0},
{0,1,1,0,1,0,0,0},
{0,1,1,0,1,0,0,0}
};

int leds4[N_LINHAS] [N_COLUNAS] = { 
{0,1,1,0,1,0,0,0},
{0,1,1,0,1,0,0,0},
{0,0,0,0,1,0,0,0},
{0,1,1,0,1,0,0,0},
{0,1,1,0,1,0,0,0}
};



int i, j;
void setup() {
for(i = 0; i < N_LINHAS; i++)
pinMode(lin[i], OUTPUT);

for(j = 0; j < N_COLUNAS; j++)
pinMode(col[j], OUTPUT);

apagartudo();
}
int desenho=4;
void loop()
{
for (i = 0; i < N_LINHAS; i++) {
  for (j = 0; j <N_COLUNAS; j++) {
 apagartudo();
 if(desenho== 1){
    if (leds[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
 }
 else if(desenho==2){
      if (leds2[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
   
 }
  else if(desenho==3){
      if (leds3[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
   
 }
  else if(desenho==4){
      if (leds4[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
   
 }
delayMicroseconds(200);
}
}
 if(millis()-tempo >= 500) {
 tempo = millis();
 if(desenho==3){desenho=4;}else{desenho=3;}
 }
}


void apagartudo() {
int i, j;
for(i = 0; i < N_LINHAS; i++)
digitalWrite (lin[i], LOW);

for(j = 0; j < N_COLUNAS; j++)
digitalWrite (col[j],HIGH);
}
