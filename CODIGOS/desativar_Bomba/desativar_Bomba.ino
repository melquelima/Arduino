#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte p1[8] = {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
byte p2[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
byte p3[8] = {0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C};
byte p4[8] = {0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E};
byte p5[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};

int celula = 0;

void setup() {
  pinMode(13,OUTPUT);
  pinMode(7,INPUT);
  lcd.begin(16, 2);
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);

}

void loop() {

int bot = digitalRead(7);
if (bot == HIGH){
lcd.setCursor(0, 0);
lcd.print("               ");
lcd.setCursor(0, 0);
lcd.print("Desativando");
   for(int i=1;i<=4;i++){
         lcd.setCursor(celula, 1);
         lcd.write(i);
         if (i == 4){celula++;tone(13,2999,90);}
         if ((i==4)&&(celula==16)){
             lcd.setCursor(0, 0);
             lcd.clear();
             lcd.print("DESATIVADA");
             bip();
             delay(3000);
            celula=0;
         }
         delay(100);
    }
}
else{
lcd.setCursor(0, 0);
lcd.print("Desativar bomba");
lcd.setCursor(0, 1);
lcd.print("               ");
celula=0; 
}
}


void bip(){
tone(13,1599,100);delay(100);tone(13,1299,100);delay(100);
 tone(13,1499,100);delay(100);tone(13,1399,100);delay(100);
tone(13,1299,100);delay(100);tone(13,1499,100);delay(1000); 
  
  {
