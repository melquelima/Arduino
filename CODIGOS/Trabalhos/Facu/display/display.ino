
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);


static const unsigned char PROGMEM coracao[] = {
0x00, 0x3F, 0xE0, 0x00, 0x00, 0x0F, 0xFC, 0x00,0x00, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0x00,
0x03, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x80,0x07, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xC0,
0x07, 0xFF, 0xFF, 0xC0, 0x07, 0xFF, 0xFF, 0xE0,0x0F, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xF0,
0x1F, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xF8,0x1F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xF8,
0x3F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xF8,0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
0x7F, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC,0x3F, 0xFF, 0xFE, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE,
0x7F, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC,0x7F, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE,
0x7F, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE,0x7F, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE,
0x7F, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC,0x3F, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE,
0x3F, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC,0x3F, 0xFF, 0xE0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC,
0x3F, 0xFF, 0xE0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC,0x1F, 0xFF, 0xE0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC,
0x1F, 0xFF, 0xC0, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8,0x0F, 0xFF, 0xC0, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8,
0x0F, 0xFF, 0x81, 0x1F, 0xFF, 0xFF, 0xFF, 0xF0,0x00, 0x00, 0x03, 0x1E, 0x00, 0x00, 0x07, 0xF0,
0x00, 0x00, 0x03, 0x1C, 0x00, 0x00, 0x03, 0xE0,0x00, 0x00, 0x02, 0x1C, 0x00, 0x00, 0x07, 0xE0,
0x00, 0x00, 0x07, 0x18, 0x00, 0x00, 0x07, 0xC0,0x01, 0xFF, 0xFF, 0x18, 0x3F, 0xFF, 0xFF, 0x80,
0x01, 0xFF, 0xFE, 0x10, 0x7F, 0xFF, 0xFF, 0x00,0x00, 0xFF, 0xFF, 0x10, 0x7F, 0xFF, 0xFF, 0x00,
0x00, 0x7F, 0xFF, 0x00, 0xFF, 0xFF, 0xFE, 0x00,0x00, 0x3F, 0xFF, 0x00, 0xFF, 0xFF, 0xFC, 0x00,
0x00, 0x1F, 0xFF, 0x01, 0xFF, 0xFF, 0xF8, 0x00,0x00, 0x1F, 0xFF, 0x01, 0xFF, 0xFF, 0xF0, 0x00,
0x00, 0x0F, 0xFF, 0x03, 0xFF, 0xFF, 0xF0, 0x00,0x00, 0x07, 0xFF, 0x03, 0xFF, 0xFF, 0xE0, 0x00,
0x00, 0x03, 0xFE, 0x07, 0xFF, 0xFF, 0xC0, 0x00,0x00, 0x01, 0xFF, 0x07, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x0F, 0xFF, 0xFF, 0x00, 0x00,0x00, 0x00, 0x3F, 0x0F, 0xFF, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x1F, 0x1F, 0xFF, 0xF8, 0x00, 0x00,0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00,0x00, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const unsigned char PROGMEM coracao2[] = 
{0x00,0x00,0x0e,0x3c,0x1f,0x7e,0x3f,0xff,0x3f,0xff,0x3f,0xff,0x1f,0xfe,0x0f,0xfc,0x07,0xf8,0x03,0xf0,0x01,0xe0,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void setup()   {                
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)

    display.clearDisplay();
       //display.fillRoundRect(0, 0, 20,8,10, WHITE);
       display.drawRoundRect(0, 0, 30,20,10, WHITE);
      //display.drawBitmap(30, 0, coracao, 126, 28, WHITE);
      //display.fillRect(95,0,40,40,BLACK);
      //display.drawRect(0,0,32,16,WHITE);
      display.drawBitmap(30, 0, coracao2, 16, 16, WHITE);
      //bateria();
    display.display();

      

}


void loop() {
  
}

void bateria(){
  int x = 103;
  int y = 0;
  display.drawRect(x, y, 20, 6, WHITE);
  display.fillRect(x, y, 10, 6, WHITE);
  display.fillRect(x+19, y+1, 4, 4, WHITE); //X Y W H
}


