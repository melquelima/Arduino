const int FRAMES_ANIMACAO = 50;
 
const int VELOCIDADE = 120; //ms
const int N_LINHAS = 5;
const int N_COLUNAS = 8;
 
int lin[N_LINHAS] = {2,3,4,5,6};
int col[N_COLUNAS] = {7,8,9,10,11,12,13,14};
 
int leds[N_LINHAS][FRAMES_ANIMACAO] = {
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
 
int i, j, k;
long long proximo;
void setup() {
 for(i = 0; i < N_LINHAS; i++)
 pinMode(lin[i], OUTPUT);
 
 for(j = 0; j < N_COLUNAS; j++)
 pinMode(col[j], OUTPUT);
 
 k = 0;
 proximo = VELOCIDADE;
 apagarTudo();
}
 
void apagarTudo() {
 int i, j;
 
 for(i = 0; i < N_LINHAS; i++)
 digitalWrite(lin[i], LOW);
 
 for(j = 0; j < N_COLUNAS; j++)
 digitalWrite(col[j], HIGH);
}
 
void loop()
{
 for(i = 0; i < N_LINHAS; i++) {
 for(j = 0; j < N_COLUNAS; j++) {
 apagarTudo();
 
 if(leds[i][j+k]) {
 digitalWrite(lin[i], HIGH);
 digitalWrite(col[j], LOW);
 }
 delayMicroseconds(250);
 }
 }
 
 if(millis() >= proximo) {
 proximo = millis() + VELOCIDADE;
 k = (k >= FRAMES_ANIMACAO-N_COLUNAS ? 0 : k+1);
 }
}
