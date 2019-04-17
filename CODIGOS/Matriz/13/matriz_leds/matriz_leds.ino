const int N_LINHAS = 5;
const int N_COLUNAS = 8;
long tempo=0;
int lin[N_LINHAS] = {2,3,4,5,6};
int col[N_COLUNAS] = {7,8,9,10,11,12,13,14};
int leds[N_LINHAS] [N_COLUNAS] = { 
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
};

void setup() {
for(int i = 0; i < N_LINHAS; i++)
pinMode(lin[i], OUTPUT);

for(int j = 0; j < N_COLUNAS; j++)
pinMode(col[j], OUTPUT);

apagartudo();
}
void loop()
{
for (int i = 0; i < N_LINHAS; i++) {
for (int j = 0; j <N_COLUNAS; j++) {
if (leds[i][j] ) {
digitalWrite (lin[i], HIGH);
digitalWrite (col[j], LOW);
}
delayMicroseconds(200);
apagartudo();
}
}
proximo();
}

void proximo(){
  if(millis()- tempo >= 200) {
   tempo = millis();
   for (int i = 0; i < N_COLUNAS; i++) 
    for (int j = N_LINHAS-1; j >=0; j--) 
      if (!leds[j][i]) {leds[j][i]=1;return;}
   
  }   
}


void apagartudo() {
for(int i = 0; i < N_LINHAS; i++)
digitalWrite (lin[i], LOW);

for(int j = 0; j < N_COLUNAS; j++)
digitalWrite (col[j],HIGH);
}

