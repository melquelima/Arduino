int R = 3;
int G = 5;
int B = 9;

// -------------- FADE
int cor_atual[3] = {0, 0, 0};
int cor_futura[3] = {0, 0, 0};
//-------------------


void config_leds(){
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
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
    
    if(flag_nota){return;}
    executa_cor();
    EN_PING();
    delay(10);
  }
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
      cor_futura[0] = 255;
      cor_futura[1] = 255;
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
 
      case 10: //verde_agua
      cor_futura[0] = 0;
      cor_futura[1] = 0;
      cor_futura[2] = 0;
      break;
 
  }
}

void executa_cor() {
  
  analogWrite(R, cor_atual[0]);
  analogWrite(G, cor_atual[1]);
  analogWrite(B, cor_atual[2]);
}

void executa_cor2() {
  
  analogWrite(R, cor_futura[0]);
  analogWrite(G, cor_futura[1]);
  analogWrite(B, cor_futura[2]);
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
