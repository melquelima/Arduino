#include <mills.h>

mills tempo(400);
const int N_LINHAS = 4;
const int N_COLUNAS = 4;
int lin[N_LINHAS] = {2, 3, 4, 5};
int col[N_COLUNAS] = {7, 11, 9, 10};
int leds[N_LINHAS] [N_COLUNAS];

boolean variavel = true;
int i, j;
void setup() {
  Serial.begin(9600);
  for (i = 0; i < N_LINHAS; i++)
    pinMode(lin[i], OUTPUT);

  for (j = 0; j < N_COLUNAS; j++)
    pinMode(col[j], OUTPUT);

  apagartudo();
  tempo.inicio();
}
void loop()
{
  if (Serial.available()) {
    int comando = Serial.read()-49;
    if(comando+49 != 'r' ){
    int x = Serial.read();
      while(x == -1){x = Serial.read();}
      x = x-49;
      leds[comando][x] = !leds[comando][x];

      comando = 0;
    }else{
     for (int i = 0; i < N_LINHAS; i++) 
    for (int j = 0; j < N_COLUNAS; j++) 
        leds[i][j]=0;
    } 
  }
  mostra();
}

void mostra() {
  for (i = 0; i < N_LINHAS; i++) {
    for (j = 0; j < N_COLUNAS; j++) {
      apagartudo();

      if (leds[i][j]) {
        digitalWrite (lin[i], LOW);
        digitalWrite (col[j], HIGH);
      }


      delayMicroseconds(200);
    }
  }


}

void apagartudo() {
  int i, j;
  for (i = 0; i < N_LINHAS; i++)
    digitalWrite (lin[i], HIGH);

  for (j = 0; j < N_COLUNAS; j++)
    digitalWrite (col[j], LOW);
}
