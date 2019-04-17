#include <Mattec.h>
#include <DS1307.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
Time t;
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

DS1307 rtc(4, 5);
 Mattec teclado(13,12,11,10,9);
  int comando; 
 int tempo[4]= {0,0,0,0};
 int crono[4]= {0,0,0,0};

int H_crono;
int M_crono;
boolean cronometro_enb = false;

void setup()
{
  lcd.init(); 
  lcd.backlight();
  rtc.halt(false);
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  Serial.begin(9600); 
}
 
void loop()
{
 
comando = teclado.gettec();
if (comando == 12)
gettempo();
if (comando == 14)
getcrono();

  lcd.setCursor(0,0);
  lcd.print("Hora: ");
  lcd.print(rtc.getTimeStr());
  cronometro();
 
 t = rtc.getTime();
  delay(100);
  
}


void configura_relogio(int x,int y){
 rtc.setTime(x, y, 50); 
}

int converte(int x){
  
  switch(x){
  case 0:
  return 1; 
  break;
  case 1:
  return 2;
  break;
  case 2:
  return 3;
  break;
  case 4:
  return 4;
  break;
  case 5:
  return 5;
  break;
  case 6:
  return 6;
  break;
  case 8:
  return 7;
  break;
  case 9:
  return 8;
  break;
  case 10:
  return 9;
  break;
  case 13:
  return 0;
  break ;
    
  }
  
}



void gettempo(){
 delay(200);
  lcd.clear();
lcd.setCursor(0,0);
  lcd.print("Configurar");
lcd.setCursor(0,1);
lcd.print("00:00");
lcd.setCursor(0,1);
lcd.blink();
tempo[0] = converte(teclado.getW());
lcd.print(tempo[0]);

delay(200);
lcd.setCursor(1,1);
tempo[1] = converte(teclado.getW());
lcd.print(tempo[1]);


delay(200);
lcd.noBlink();
lcd.setCursor(3,1);
lcd.blink();
tempo[2] = converte(teclado.getW());
lcd.print(tempo[2]);

delay(200);
lcd.setCursor(4,1);
tempo[3] = converte(teclado.getW());
lcd.print(tempo[3]);
lcd.noBlink();
lcd.clear();

int hora  = tempo[0]*10 + tempo[1];
int minutos = tempo[2]*10 + tempo[3];
configura_relogio(hora,minutos);

comando = 99; 
}

void getcrono(){

delay(200);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Confg Cronometro");
lcd.setCursor(0,1);
lcd.print("00:00");
lcd.setCursor(0,1);
lcd.blink();
crono[0] = converte(teclado.getW());
lcd.print(crono[0]);

delay(200);
lcd.setCursor(1,1);
crono[1] = converte(teclado.getW());
lcd.print(crono[1]);


delay(200);
lcd.noBlink();
lcd.setCursor(3,1);
lcd.blink();
crono[2] = converte(teclado.getW());
lcd.print(crono[2]);

delay(200);
lcd.setCursor(4,1);
crono[3] = converte(teclado.getW());
lcd.print(crono[3]);
lcd.noBlink();
lcd.clear();

 H_crono  = crono[0]*10 + crono[1];
 M_crono = crono[2]*10 + crono[3];

comando = 99;
cronometro_enb = true;

}

void cronometro(){

if(cronometro_enb){
  
  int hora = t.hour;
  int minuto = t.min;
  
  if(hora == H_crono && minuto == M_crono)
  {
    lcd.setCursor(0,1);
   lcd.print("Esta na hora"); 
   cronometro_enb = false;
  }
  
 }  
}
