//Programa : Teste display Nokia 5110 usando biblioteca Adafruit
//Autor : Arduino e Cia

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>
// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

void setup()   
{
  Serial.begin(9600);
  display.begin();
  display.setContrast(50); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(0,0);  //Seta a posição do cursor
  //display.println("Arduino & Cia!");  

  //Texto invertido - Branco com fundo preto
  //display.setTextColor(WHITE, BLACK); 

  //display.println("Arduino & Cia!");

  display.setTextSize(1.5); 
  display.setTextColor(BLACK);
  display.print("Variometro");
  //display.display();
  //delay(2000);
  
  //display.clearDisplay();
  //for (int j = 0; j<=48;j++)
  //for (int i = 0; i<=84;i++){ 
  //display.drawPixel(i,j, BLACK);
 // display.display();
//}
 //display.fillCircle(30,15, 10, BLACK);
  display.drawRoundRect(0,0,40,20,3,2);
  display.drawRoundRect(41,0,40,20,3,2);
  display.drawRoundRect(0,21,81,20,3,2);
  
  //display.setCursor(10,5);
  //display.print("20 C");
  //display.drawCircle(25,6,1,1);
   //display.fillRect(50,13,23,10,1);
   
   display.display();
}

void loop()
{

}
