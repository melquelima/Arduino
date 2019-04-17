
#include <LiquidCrystal.h>  

#define Buzzer   13   // porta que o buzzer se encontra
#define bUp      07  // porta do botao de navegação
#define action   8   // porta onde o botao de açao se encontra
char state = 1;      // variavel criada e agregada o valor 1 -- Esta variavel sera lida e é ela quem devine a tela de navegação ATUAL
int segundos = 10;   // variavel segundos agregada um valor de 10s
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // portas onde se encontra o LCD
boolean Menu1,Menu2;      //variavel boolean de ação   essas variaveis determinan qual a açao sera executada
void setup()
{
  lcd.begin(16, 2);
  pinMode(Buzzer, OUTPUT);  // Buzzer
  pinMode(action, OUTPUT);  // Botao de açao
  pinMode(bUp,    INPUT); // Botao de navegação
}

void loop()
{
  
  // -------------------------------------Esta parte e a navegação do menu----------
  int bot = digitalRead(bUp);delay(100);
  if (bot == HIGH){                            // se botao de navegação pressionado pule pra próxima tela
    if (state==1){state=2;}
    else if(state==2){state=1;} 
  }
  
    //-------------------Esta parte determina oque irá aparecer na tela-----------------
  if (state == 1){                 //se estate for igual a 1 mostre segundos na tela
  lcd.setCursor(0,0);
      lcd.print("Segundos:");
      lcd.setCursor(0,1);
      lcd.print(segundos);
      lcd.print("s");
      Menu1=true;
      Menu2=false;
  }
  else if(state == 2){             // se state for igual a 2 mostre buzzer na tela
  lcd.setCursor(0,0);
      lcd.print("BUZZER   ");
      lcd.setCursor(0,1);
      lcd.print("           ");
      Menu1=false;
      Menu2=true;
      
  }
  
  // ----------------------------------Esta parte e a ação da tela -------------
  int acao = digitalRead(action);delay(100);    
  if (acao == HIGH){                             // se botao de ação precionado ele verifica a tela (state) que vc se encontra e determina uma certa função
   if (Menu1 == true){segundos++;}               // se estiver na tela 1 (state1) adcione 1 a variavel segundos
   else if(Menu2 == true){                       // se estiver na tela 2 (state2) toque um som no buzzer
   tone(13,1599,100);delay(100);tone(13,1299,100);delay(100);tone(13,1499,100);delay(100);tone(13,1399,100);delay(100);tone(13,1299,100);delay(100);tone(13,1499,100);delay(1000);}
  }
}


