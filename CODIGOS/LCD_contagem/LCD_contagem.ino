// adicionar ao projecto a livraria que permite usar o LCD de 16x2
#include <LiquidCrystal.h>
int segundos=0;
 
int botao = 7; // porta a usar para ligar o botão
 
int estadobotao=0; //Guarda o estado do botão
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //variável com a informação dos pinos a usar na comunicação com o display
 
void setup() {
 
pinMode(botao, INPUT); // inicialização do pino defenido para o botão como sendo uma entrada
 
lcd.begin(16, 2); //inicialização do display
 
lcd.print("PPLWARE"); //escrita na primeira linha do display
 
}
 
void loop() {
 
delay(1000); //período de espera de um segundo
 
segundos++; //incrementação da variável que guarda o tempo da contagem
 
lcd.setCursor(0, 1); //deslocamento do cursor de escrita no display para o inicio da segunda linha
 
lcd.print("contagem:"); // escrita do texto "contagem: " no display
 
lcd.setCursor(10, 1); // deslocamento do cursor de escrita para a segunda linha e para a decima coluna
 
lcd.print(segundos); // escrita do conteúdo da variável 'segundos'

estadobotao= digitalRead(botao); // le o estado do pino onde está ligado o botão
 
if (estadobotao == HIGH) { // verifica se o botão está premido, e se sim entra
 
segundos=0; // coloca a variável que guarda o tempo a '0'

lcd.setCursor(0, 1); //deslocamento do cursor de escrita no display para o inicio da segunda linha
 
lcd.print(" "); // limpa a segunda linha do display.
 
}
 
}
