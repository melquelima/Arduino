#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int i;

void setup()
{
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,1);
lcd.print("TESTANDO LCD AUTOSCROLL()");

}

void loop()
{

lcd.setCursor(16,1);
lcd.autoscroll();
lcd.print(" ");
delay(300);
}
