//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

HX711 BL1(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library
HX711 BL2(A2, A3);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display


int rele_motor = 4;
int steep = 9;
float C1 = 117.75;
double C2 = 8.7; 
unsigned long int peso_moto=70334;
unsigned long int F_frenagem = 185;
float porc1 = 0;
float porc2 = 0;


void setup()
{
  Serial.begin(9600);

  pinMode(steep,INPUT_PULLUP);
  pinMode(rele_motor,OUTPUT);  
  BL1.set_scale(C1);
  BL1.tare();
  BL2.set_scale(C2);
  BL2.tare();
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  lcd.print("Visual Maquinas");
  lcd.setCursor(0,1);
  lcd.print("Frenow");
  delay(5000); 

  lcd.clear();
  lcd.setCursor(0,0);
  lcdprint("Pressione para",0,0);
  lcdprint("iniciar",1,0);

}

void loop()
{

  if(!digitalRead(steep)){

    lcdprint("RODA DIANTEIRA",0,0);
    lcdprint("PARA PESAGEM",1,0);
    delay(1000);
    while(digitalRead(steep)){
    }

    config_peso();
    lcd.clear();

    lcdprint("Pressione para",0,0);
    lcdprint("continuar",1,0);


    while(digitalRead(steep)){
    }
    inicia(1);
    //---------------------------------------2 RODA
    delay(5000);
    
    lcd.clear();
    
    lcdprint("PRESSIONE PARA",0,0);
    lcdprint("PROSSEGUIR",1,0);

    lcd.clear();
    
    lcdprint("RODA TRASEIRA",0,0);
    lcdprint("PARA PESAGEM",1,0);
    delay(1000);
    while(digitalRead(steep)){
    }

    config_peso();
    lcd.clear();

    lcdprint("Pressione para",0,0);
    lcdprint("continuar",1,0);


    while(digitalRead(steep)){
    }
    inicia(0);
    
    delay(2000);
    
    lcd.clear();
    float total = porc1 + porc2;
    lcdprint("Ef total: ",0,0);
    lcd.print(total);
    lcdprint((total>50?"APROVADO":"REPROVADO"),1,0);
    while(1){}
    

  }


  //inicia();

  //while(1){}
  /*
  double peso = _getpeso(0);
   double peso2 = _getpeso(1);
   
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("BL1: ");
   lcd.print(peso);
   lcd.setCursor(0,1);
   lcd.print("BL2: ");
   lcd.print(peso2);
   delay(500);
   */
}

void inicia(int x){
  lcd.clear();
  lcdprint("===INICIANDO===",0,0);
  delay(5000);
  lcdprint((x?"RODA DIANTEIRA":"RODA TRASEIRA"),0,0);
  lcdprint("NO FRENOMETRO",1,0);
  while(digitalRead(steep)){
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Iniciar o teste");
  lcd.setCursor(0,1);
  lcd.print("de Frenagem");
  while(digitalRead(steep)){
  }



  lcd.clear();
  digitalWrite(rele_motor,1);
  acelera(10);
  delay(1000);
  freia(5);
  leitura(0);
  digitalWrite(rele_motor,0);
  calcula(x);
}

void calcula(int y){
  lcd.clear();
  lcdprint("=====RESULTADO=====",0,0);
  lcdprint("Efic: ",1,0);
  unsigned long int M =F_frenagem*24;
  Serial.print("M = >");
  Serial.println(M);
  Serial.print("peso_moto = >");
  Serial.println(peso_moto);

  float A = (float(M)/float(peso_moto));
  Serial.print("A == >");
  Serial.println(A,4); 

  float porcentagem = A*100;
  Serial.print("% == >");
  Serial.println(porcentagem);
  lcd.setCursor(6,1);
  lcd.print(porcentagem);
  lcd.print("%");
  porc1 = (y?porcentagem:porc1);
  porc2 = (!y?porcentagem:porc2);

}

void lcdprint(String txt,int linha,int coluna){
  lcd.setCursor(coluna,linha);
  lcd.print(txt); 
}


double _getpeso(int x){
  double peso = 0;  
  if (!x){
    BL1.power_up();
    peso = BL1.get_units(10);
    BL1.power_down();			        // put the ADC in sleep mode  
  }
  else{
    BL2.power_up();
    peso = BL2.get_units(10);
    BL2.power_down();  
  }

  Serial.println(peso);
  //return peso;
  return (peso<0?0:peso);  
}









