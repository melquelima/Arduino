
#include <LiquidCrystal.h>  

#define Buzzer   13
#define bUp      7
#define bDown    9
#define action   8

char state = 1; // define a tela atual
int segundos = 10; // segundos que aparece na tela 1

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
  lcd.begin(16, 2);
  pinMode(Buzzer, OUTPUT);
  pinMode(bUp,    INPUT);
  pinMode(bDown,  INPUT);
}

void loop()
{
  
  if (digitalRead(bUp)){ // se o botao pra cima for presionado
    delay(100);           // tempo para tirar o dedo do botao
    state = (state == 3?1:state+1); // muda a variavel que seta a tela atual
  }

  if (digitalRead(bDown)){ // se o botao pra bqixo for presionado
    delay(100);             // tempo para tirar o dedo do botao
    state = (state ==1?3:state-1);// muda a variavel que seta a tela atual
   }
 
  if (digitalRead(action)){ // se botao de ação selecionado
    delay(100);             // tempo para tirar o dedo do botao
   if (state == 1){segundos=segundos+10;} //TELA 1 - identifica a tela que se encontra e realiza determinada ação correnspodente
   else 
     if(state == 2){tone(13,1599,100);delay(100);tone(13,1299,100);delay(100);tone(13,1499,100);delay(100);tone(13,1399,100);delay(100);tone(13,1299,100);delay(100);tone(13,1499,100);delay(1000);} // TELA2
   else 
     if(state == 3){lcd.setCursor(0,1); lcd.print("Funciona");}  // TELA 3
  }
  
  
  if (state == 1){ //TELA 1 -  verifica a tela atual e printa seus valores
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Segundos:");
      lcd.setCursor(0,1);
      lcd.print(segundos);
      lcd.print("s");

  }
  else if(state == 2){ // TELA 2
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BUZZER");
      
  }
  else if(state == 3){ // TELA 3
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Texto");      
  }
}

