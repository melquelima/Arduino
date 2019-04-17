#include "DHT.h"
#define DHTPIN 11     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display



DHT dht(DHTPIN, DHTTYPE);

int C_aquece = 8;
int C_esfria = 9;
int resist = 4;

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  pinMode(C_aquece, OUTPUT);
  pinMode(C_esfria, OUTPUT);
  pinMode(resist, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = temperatura();

  if (temp == 0) {
    //ERRO
  } else {
    if (temp > 32) esfria();
    if (temp < 30) aquece();
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);

}


void aquece() {

  while (temperatura() < 31) {
    digitalWrite(C_aquece, 1);
    digitalWrite(resist, 1);
    digitalWrite(C_esfria, 0);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura());
 
    lcd.setCursor(0, 1);
    lcd.print("Aquecendo...");

  }
  digitalWrite(C_aquece, 0);
  digitalWrite(resist, 0);
  digitalWrite(C_esfria, 0);
}


void esfria() {

  while (temperatura() > 31) {
    digitalWrite(C_aquece, 0);
    digitalWrite(resist, 0);
    digitalWrite(C_esfria, 1);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura());
 
    lcd.setCursor(0, 1);
    lcd.print("Esfriando...");
  }
  digitalWrite(C_aquece, 0);
  digitalWrite(resist, 0);
  digitalWrite(C_esfria, 0);
}


float temperatura() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    return 0;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  return hic;

}

