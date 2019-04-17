#include <mills.h>
#include <AH_74HC595.h>

mills tempo(1);
#define SER_Pin   10   //Serial data input
#define RCLK_Pin  11   //Register clock
#define SRCLK_Pin 12   //Shift register clock
int numero[6] = {0, 0, 1, 1, 1, 6};
int dig = 2;
AH_74HC595 seven_segment(SER_Pin, RCLK_Pin, SRCLK_Pin);
boolean mostrar  = false;
int comeco = inicio();
void setup() {
  seven_segment.clear();
  tempo.inicio();
  for(int i=2;i<=7;i++)
  pinMode(i, OUTPUT);
}

void loop() {
 disp();
}

int inicio() {
  for (int i = 0; i <= 5; i++) {
    if (numero[i] != 0)
      return i;
  }
}

void disp(){
  
  if (tempo.verifica()) {
    seven_segment.clear();
    digitalWrite(dig, HIGH);
    digitalWrite((dig == 2 ? 7 : dig - 1), LOW);
    if (dig - 2 == comeco) {
      mostrar = true;
    }

    if (mostrar)  {seven_segment.showNumber(numero[dig - 2]); delayMicroseconds(1800);}
    if (dig == 7) {
      mostrar = false;
    }
    dig = (dig == 7 ? 2 : dig + 1);
    
    tempo.inicio();
  }
  
}
