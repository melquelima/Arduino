const int N_LINHAS = 5;
const int N_COLUNAS = 8;
int lin[N_LINHAS] = {2,3,4,5,6};
int col[N_COLUNAS] = {7,8,9,10,11,12,13,14};
int leds[N_LINHAS] [N_COLUNAS] = { 
{0,0,1,0,0,1,0,0}, // faça seu desenho aki
{0,1,1,1,1,1,1,0},
{0,1,1,1,1,1,1,0},
{0,0,1,1,1,1,0,0},
{0,0,0,1,1,0,0,0}
};

int i, j;
void setup() {
for(i = 0; i < N_LINHAS; i++)
pinMode(lin[i], OUTPUT);

for(j = 0; j < N_COLUNAS; j++)
pinMode(col[j], OUTPUT);

apagartudo();
}
void loop()
{
for (i = 0; i < N_LINHAS; i++) {
for (j = 0; j <N_COLUNAS; j++) {
  apagartudo();
if (leds[i][j+0] ) {
digitalWrite (lin[i], HIGH);
digitalWrite (col[j], LOW);
}
delayMicroseconds(200);
}
}
}



void apagartudo() {
int i, j;
for(i = 0; i < N_LINHAS; i++)
digitalWrite (lin[i], LOW);

for(j = 0; j < N_COLUNAS; j++)
digitalWrite (col[j],HIGH);
}
