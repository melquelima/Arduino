// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Estes são os pino utilizados pelo LCD
int contador = 10000; // Para disparar o Relé no final da contagem
void setup() {
pinMode(8, OUTPUT);  // Definindo o pino 13 como saída para acionar o Relé no final da contagem
// set up the LCD's number of columns and rows: 
lcd.begin(16, 2);
// Print a message to the LCD.
lcd.print("Contagem regressiva"); // Basta alterar a mensagem que vai aparecer
}
void loop() {
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 1);
// print the number of seconds since reset:
//lcd.print(millis()/1000);
//Contando
  lcd.print(contador--);
  //Condicional para ativar o relé
  if(contador <=0){
    digitalWrite(8, HIGH);
  }
}
