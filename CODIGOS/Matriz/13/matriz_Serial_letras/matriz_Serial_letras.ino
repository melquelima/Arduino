const int N_LINHAS = 5;
const int N_COLUNAS = 8;
int lin[N_LINHAS] = {2,3,4,5,6};
int col[N_COLUNAS] = {7,8,9,10,11,12,13,14};
int A[N_LINHAS] [N_COLUNAS] = { 
{0,0,1,1,1,0,0,0},
{0,1,0,0,0,1,0,0},
{0,1,1,1,1,1,0,0},
{0,1,0,0,0,1,0,0},
{0,1,0,0,0,1,0,0}
};

int B[N_LINHAS] [N_COLUNAS] = { 
{0,1,1,1,0,0,0,0},
{0,1,0,0,1,0,0,0},
{0,1,0,1,0,0,0,0},
{0,1,0,0,1,0,0,0},
{0,1,1,1,0,0,0,0}
};

int C[N_LINHAS] [N_COLUNAS] = { 
{0,0,1,1,1,0,0,0},
{0,1,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0},
{0,0,1,1,1,0,0,0}
};

int D[N_LINHAS] [N_COLUNAS] = { 
{0,1,1,0,0,0,0,0},
{0,1,0,1,0,0,0,0},
{0,1,0,1,0,0,0,0},
{0,1,0,1,0,0,0,0},
{0,1,1,0,0,0,0,0}
};



int i, j;
void setup() {
  Serial.begin(9600);
for(i = 0; i < N_LINHAS; i++)
pinMode(lin[i], OUTPUT);

for(j = 0; j < N_COLUNAS; j++)
pinMode(col[j], OUTPUT);

apagartudo();
}
char letra;
void loop()
{
   serial();
for (i = 0; i < N_LINHAS; i++) {
  for (j = 0; j <N_COLUNAS; j++) {
 apagartudo();
 if(letra== 'a'){
    if (A[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
 }
 else if(letra=='b'){
      if (B[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
   
 }
  else if(letra=='c'){
      if (C[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
   
 }
  else if(letra=='d'){
      if (D[i][j] ) {   
      digitalWrite (lin[i], HIGH);
      digitalWrite (col[j], LOW);
      }
   
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

void serial(){
 if (Serial.available() >0){
  letra = Serial.read();
  Serial.println(letra);
 }  
}
