#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // RX, TX
// -------------- FADE
int cor_atual[3] = {0, 0, 0};
int cor_futura[3] = {0, 0, 0};
int corr = 1;
//-------------------

int R;
int G;
int B;
int atual  = 1;
String valor_R;
String valor_G;
String valor_B;
int dec = 1;
int tempo = 0;
boolean F_habilita = false;


void setup()
{
  mySerial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void loop() // run over and over
{
  
    while(F_habilita){
  cor(corr);
  fade();
  delay(tempo*1000);
  corr = (corr != 9?corr+1:1);
  }
  
  int texto = mySerial.read();
  delay(10);
  if (texto == 67) {
    
    while (mySerial.available()) {
      char comando = mySerial.read();
      if (comando != 'C' && comando != '$')
      {
        if (comando != '/') {
          if (dec == 1) {
            valor_R += comando;
          }
          if (dec == 2) {
            valor_G += comando;
          }
          if (dec == 3) {
            valor_B += comando;
          }
        } else {
          dec += (dec == 3 ? -2 : 1);
        }

      }
      if ( comando == '$') {
        
        converte();
        if (R <= 255 && R >= 0) {
          Serial.print("R: ");
          Serial.print(R);
          Serial.print(" G: ");
          Serial.print(G);
          Serial.print(" B: ");
          Serial.println(B);
          analogWrite(9, R);
          analogWrite(10, G);
          analogWrite(11, B);
        }
        dec = 1;
        valor_R = "";
        valor_G = "";
        valor_B = "";
      }
    }
  }
  if (texto == 70) {
    int comando = mySerial.read() - 48;
    Serial.print("Tempo :");
    Serial.println(comando);
    tempo = comando;
    Serial.println(tempo);
    F_habilita = !F_habilita;
  }
}
void converte() {
  R = valor_R.toInt();
  G = valor_G.toInt();
  B = valor_B.toInt();
}
//============================== FADE



void fade() {
  boolean saii = true;
  while (!igual()&& saii) {
    
  if(mySerial.available()){
   F_habilita = false;
saii = false;   
   analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  }
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
    delay(50);
//    Serial.print(cor_atual[0]);
//    Serial.print("  ");
//    Serial.print(cor_atual[1]);
//    Serial.print("  ");
//    Serial.println(cor_atual[2]);
  }
//  Serial.println("Saiu");
}

void executa_cor() {
  
  analogWrite(9, cor_atual[0]);
  analogWrite(10, cor_atual[1]);
  analogWrite(11, cor_atual[2]);
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
