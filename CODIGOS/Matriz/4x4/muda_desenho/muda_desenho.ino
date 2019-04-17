#include <mills.h>

mills tempo(400);
const int N_LINHAS = 4;
const int N_COLUNAS = 4;
int lin[N_LINHAS] = {2, 3, 4, 5};
int col[N_COLUNAS] = {7, 11, 9, 10};
int leds[N_LINHAS] [N_COLUNAS] = {
  {1, 0, 0, 1}, // faça seu desenho aki
  {0, 1, 1, 0},
  {0, 1, 1, 0},
  {1, 0, 0, 1}
};

int leds2[N_LINHAS] [N_COLUNAS] = {
  {0, 1, 1, 0}, // faça seu desenho aki
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0}
};
boolean variavel = true;
int i, j;
void setup() {
  for (i = 0; i < N_LINHAS; i++)
    pinMode(lin[i], OUTPUT);

  for (j = 0; j < N_COLUNAS; j++)
    pinMode(col[j], OUTPUT);

  apagartudo();
  tempo.inicio();
}
void loop()
{
  for (i = 0; i < N_LINHAS; i++) {
    for (j = 0; j < N_COLUNAS; j++) {
      apagartudo();
      
        if (leds[i][j]&& variavel) {
          digitalWrite (lin[i], LOW);
          digitalWrite (col[j], HIGH);
        }
         if (leds2[i][j] && !variavel) {
          digitalWrite (lin[i], LOW);
          digitalWrite (col[j], HIGH);
        }
      
      delayMicroseconds(200);
    }
  }
  
  if(tempo.verifica()){
   variavel = !variavel; 
  }
}



void apagartudo() {
  int i, j;
  for (i = 0; i < N_LINHAS; i++)
    digitalWrite (lin[i], HIGH);

  for (j = 0; j < N_COLUNAS; j++)
    digitalWrite (col[j], LOW);
}
