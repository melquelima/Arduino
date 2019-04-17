// -------------- FADE
int cor_atual[3] = {0, 0, 0};
int cor_futura[3] = {0, 0, 0};
int corr = 1;
//-------------------

int R = 5;
int G = 6;
int B = 7;

void setup()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  Serial.begin(9600);
}

void loop() // run over and over
{
  
    while(1){
  cor(corr);
  fade();
  delay(1000);
  corr = (corr != 9?corr+1:1);
  }
  
 
}

void fade() {
  boolean saii = true;
  while (!igual()) {
    
    if (!igual(0)) {
      cor_atual[0] = (cor_atual[0] > cor_futura[0] ? cor_atual[0] - 1 : cor_atual[0] + 1);
      cor_atual[0] = (cor_atual[0] <= 0 ? 0 : cor_atual[0]);
    }

    if (!igual(1)) {
      cor_atual[1] = (cor_atual[1] > cor_futura[1] ? cor_atual[1] - 1 : cor_atual[1] + 1);
      cor_atual[1] = (cor_atual[1] < 0 ? 0 : cor_atual[1]);
    }
    if (!igual(2)) {
      cor_atual[2] = (cor_atual[2] > cor_futura[2] ? cor_atual[2] - 1 : cor_atual[2] + 1);
      cor_atual[2] = (cor_atual[2] <= 0 ? 0 : cor_atual[2]);
      
    }
    executa_cor();
    delay(10);
  }
}

void executa_cor() {
  
  analogWrite(R, cor_atual[0]);
  analogWrite(G, cor_atual[1]);
  analogWrite(B, cor_atual[2]);
}

boolean igual() {
  if (cor_atual[0] == cor_futura[0])
    if (cor_atual[1] == cor_futura[1])
      if (cor_atual[2] == cor_futura[2])
        return true;

  return false;
}

boolean igual(int x) {
if(cor_atual[x] == cor_futura[x])
return true;
return false;
}

void cor(int cor) {
  switch (cor) {
    case 1: //Vermelho
      cor_futura[0] = 255;
      cor_futura[1] = 0;
      cor_futura[2] = 0;
      break;
    case 2: //Verde
      cor_futura[0] = 0;
      cor_futura[1] = 255;
      cor_futura[2] = 0;
      break;
    case 3:  //Azul
      cor_futura[0] = 0;
      cor_futura[1] = 0;
      cor_futura[2] = 255;
      break;
    case 4:  //Branco
      cor_futura[0] = 255;
      cor_futura[1] = 255;
      cor_futura[2] = 255;
      break;
    case 5: //Rosa
      cor_futura[0] = 255;
      cor_futura[1] = 0;
      cor_futura[2] = 50;
      break;
    case 6: //Roxo
      cor_futura[0] = 255;
      cor_futura[1] = 0;
      cor_futura[2] = 255;
      break;
    case 7: //Laranja
      cor_futura[0] = 0;
      cor_futura[1] = 0;
      cor_futura[2] = 0;
      break;
    case 8: //Ciano
      cor_futura[0] = 0;
      cor_futura[1] = 255;
      cor_futura[2] = 255;
      break;
      
      case 9: //verde_agua
      cor_futura[0] = 0;
      cor_futura[1] = 255;
      cor_futura[2] = 50;
      break;
  }
}
