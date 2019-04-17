#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(32,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd2(39,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

int portas[3]= {11,12,13};

void setup()
{
  lcd.init();  
  lcd.backlight();
  lcd2.init();  
  lcd2.backlight();
  pinMode(portas[0],OUTPUT);
  pinMode(portas[1],OUTPUT);
  pinMode(portas[2],OUTPUT);
  pinMode(A1,INPUT);
}

void loop()
{
 lcd.clear();
 lcd2.clear();
 
  lcd.print("A:");
  lcd.print(anlgRead(1));
  
  lcd.setCursor(8,0);
  lcd.print("B:");
  lcd.print(anlgRead(2));
  
  lcd.setCursor(0,1);
  lcd.print("C:"); 
  lcd.print(anlgRead(3));
  
  lcd.setCursor(8,1);
  lcd.print("D:");
  lcd.print(anlgRead(4));
  
  lcd2.setCursor(0,0);
  lcd2.print("E:");
  lcd2.print(anlgRead(5));
  
  lcd2.setCursor(8,0);
  lcd2.print("F:");
  lcd2.print(anlgRead(6));
 
  lcd2.setCursor(0,1);
  lcd2.print("G:");
  lcd2.print(anlgRead(7));
  
  lcd2.setCursor(8,1);
  lcd2.print("H:");
  lcd2.print(anlgRead(8));
  delay(100);
}


void mux(int porta){ 
  int prt = porta-1;
  for(int i=0;i<=2;i++){
   if(prt&(1<<i))digitalWrite(portas[i],1);
   else digitalWrite(portas[i],0);
  }
}

int anlgRead(int x){
mux(x);
return analogRead(A0); 
}
