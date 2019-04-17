#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte heart[8] = { 
0b00000, // vetor de bytes correspondentes
0b01010,  // ao desenho do coração
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};

byte smile[8] = { 
0b00000, // vetor de bytes correspondentes
0b00100,  // ao desenho do coração
0b10010,
0b00010,
0b00010,
0b10010,
0b00100,
0b00000
};

void setup()
{
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print(" engenheirando! ");

lcd.createChar(1, heart); // envia nosso character p/ o display
lcd.createChar(2, smile);
}

void loop()
{
lcd.setCursor(3,1);
lcd.write(1); // desenha o coração
lcd.write(2);
delay(500);
lcd.setCursor(3,1);
lcd.print("  "); // Após 0.5s apaga o coração, assim ele
delay(500); // ficará piscando
}
