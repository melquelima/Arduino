#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x38,8,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
  lcd.setCursor(0,1);
}

void loop()
{
  if(Serial.available()){
    lcd.clear();
    lcd.print(Serial.readString());
      lcd.setCursor(2,1);
  lcd.print("Br");
  }
  
}
