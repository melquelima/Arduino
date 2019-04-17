/*************************************************************************
* Demo sketch for MicroLCD library
* Distributed under GPL v2.0
* Copyright (c) 2013-2014 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
* For more information, please visit http://arduinodev.com
*************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>

//LCD_SH1106 lcd; /* for SH1106 OLED module */
LCD_SSD1306 lcd; /* for SSD1306 OLED module */

const PROGMEM uint8_t smile[48 * 48 / 8] = {
0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xE0,
0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0,
0xE0, 0xE0, 0xF0, 0xF0, 0xE0, 0xF0, 0xE0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x3F, 0x0F, 0x0F, 0x1F, 0xFF, 0xFE, 0xFC, 0xF8, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF0, 0x00,
0x00, 0x0B, 0x3F, 0x7F, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0x7F, 0x7F, 0x7F, 0x3F, 0x07, 0x00,
0x00, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0x7F, 0x7F,
0x7F, 0x7F, 0x7F, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x17, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x1C, 0x1C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
0xFE, 0xF7, 0x00, 0x00, 0x0F, 0x03, 0x01, 0xC0, 0xF0, 0xFC, 0xFC, 0xFC, 0xF8, 0xFC, 0xFC, 0xFC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3F, 0x1F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x0F, 0x1F, 0x1F,
0x7F, 0xFD, 0xE0, 0xE0, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const PROGMEM uint8_t tick[16 * 16 / 8] =
{0x00,0x80,0xC0,0xE0,0xC0,0x80,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x78,0x30,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00};

const PROGMEM uint8_t cross[16 * 16 / 8] =
{0x00,0x0C,0x1C,0x3C,0x78,0xF0,0xE0,0xC0,0xE0,0xF0,0x78,0x3C,0x1C,0x0C,0x00,0x00,0x00,0x30,0x38,0x3C,0x1E,0x0F,0x07,0x03,0x07,0x0F,0x1E,0x3C,0x38,0x30,0x00,0x00};

void setup()
{
	lcd.begin();
lcd.clear();
	lcd.setCursor(0, 1);
	lcd.draw(smile, 48, 48);

}
void loop()
{
	lcd.clear();
	lcd.setCursor(40, 1);
	lcd.draw(smile, 48, 48);
	delay(1000);

	lcd.clear();
	lcd.setFontSize(FONT_SIZE_SMALL);
	lcd.println("Hello, world!");
	lcd.setFontSize(FONT_SIZE_MEDIUM);
	lcd.println("Hello, world!");
	delay(1000);

	lcd.setCursor(40, 6);
	lcd.draw(tick, 16, 16);
	lcd.setCursor(72, 6);
	lcd.draw(cross, 16, 16);
	delay(1000);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_SMALL);
	lcd.printLong(12345678);
	delay(1000);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_MEDIUM);
	lcd.printLong(12345678);
	delay(1000);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_LARGE);
	lcd.printLong(12345678);
	delay(1000);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_XLARGE);
	lcd.printLong(12345678);
	delay(1000);
}

