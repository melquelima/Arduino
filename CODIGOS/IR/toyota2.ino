int count_abrir = 0; //variavel a receber a quantidade de pulsos
int botao_abrir = 3; // variavel que define a porta 3 como entrada

int count_fechar = 0; //variavel a receber a quantidade de pulsos
int botao_fechar = 2; // variavel que define a porta 2 como entrada




const int piscas = 5;    // saida em rele para accionar os piscas
const int vidros_fechar = 7;   // saida em transistor para accionar os reles
const int vidros_abrir = 6;  // saida em transistor para accionar os reles

// porta 10 saida para altifalante atacado por um transistor de potencia (tip31),
//sob ordens da função tone

boolean comando = true; // variavel que determina a função a ser executada

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode(botao_abrir, INPUT_PULLUP);
pinMode(botao_fechar, INPUT_PULLUP);
pinMode(piscas, OUTPUT);
pinMode(vidros_fechar, OUTPUT);
pinMode(vidros_abrir, OUTPUT);




tone(10, 9999,  101);
delay (100);
tone(10, 8440,  101);
delay (100);
tone(10, 7440,  101);
delay (100);
tone(10, 6440,  101);
delay (100);
tone(10, 9999,  101);
delay (100);
tone(10, 8440,  101);
delay (100);
tone(10, 7440,  101);
delay (100);
tone(10, 6440,  101);



}

void loop() {
{
// comandos  para fechar
// simples toque fecha as portas e vidros, acende os piscas
// toque prolongado, fecha as portas acende os piscas mas nao fecha os vidros


if (!digitalRead(botao_fechar)) { //se o botao for pressionado
count_fechar = 0; //zera count
while (!digitalRead(botao_fechar)) { // enquanto o botao estiver pressionado
count_fechar++; // adiciona mais 1 a count
delay(200); // espera 200milisegundos
if (count_fechar == 5) { // verifica se count e' igual a 5 se for
Serial.println(" piscas fechar"); //printa vidros_fechar, piscas fechar
comando = false; // indica que a outra função nao sera executada







digitalWrite(piscas, HIGH);
delay (136);
digitalWrite(piscas, LOW);
delay (136);
digitalWrite(piscas, HIGH);   
delay (136);
digitalWrite(piscas, LOW);
delay (136);
digitalWrite(piscas, HIGH);
    
tone(10, 2440, 5);
delay (100);
tone(10, 2440, 5);
delay (100);
tone(10, 2440, 5);




while (!digitalRead(botao_fechar)) {} // espera o usuario tirar o dedo do botao
}
}
if (comando) // se comando for igual a true

Serial.println("vidros_fechar,piscas fechar"); //printa piscas fechar




comando = true; // seta comando como true


digitalWrite(vidros_fechar, HIGH);
digitalWrite(piscas, HIGH);

tone(10, 660, 200);
delay (50);
tone(10, 550, 200);
delay (50);
tone(10, 440, 200);
delay (50);
tone(10, 330, 200);
delay (50);
tone(10, 220, 200);
delay (50);

digitalWrite(piscas, HIGH);
delay (250);
digitalWrite(piscas, LOW);
delay (136);
digitalWrite(piscas, HIGH);
delay (136);
digitalWrite(piscas, LOW);
delay (136);
digitalWrite(piscas, HIGH);
delay (136);
digitalWrite(piscas, LOW);
delay (136);
digitalWrite(piscas, HIGH);
delay (136);
digitalWrite(piscas, LOW);
delay (136);


digitalWrite(vidros_fechar, LOW);
delay (500);
digitalWrite(piscas, LOW);


}
}







{
  
  
  // comandos  para fechar
  // simples toque abre as portas , acende os piscas
  // toque prolongado, abre as portas e os vidros, acende os piscas 


if (!digitalRead(botao_abrir)) { //se o botao for pressionado
count_abrir = 0; //zera count
while (!digitalRead(botao_abrir)) { // enquanto o botao estiver pressionado
count_abrir++; // adiciona mais 1 a count
delay(200); // espera 200milisegundos
if (count_abrir == 5) { // verifica se count e' igual a 5 se for
Serial.println("vidros_abrir, piscas abrir"); //printa vidros_abrir, piscas abrir
comando = false; // indica que a outra função nao sera executada

digitalWrite(vidros_abrir, HIGH);
tone(10, 2440, 5);
delay (100);
tone(10, 2440, 5);
delay (100);
tone(10, 2440, 5);




while (!digitalRead(botao_abrir)) {} // espera o usuario tirar o dedo do botao
}
}
if (comando) // se comando for igual a true

Serial.println("piscas abrir"); //printa piscas abrir




comando = true; // seta comando como true
digitalWrite(piscas, HIGH);
tone(10, 220, 200);
delay (50);
tone(10, 330, 200);
delay (50);
tone(10, 440, 200);
delay (50);
tone(10, 550, 200);
delay (50);
tone(10, 660, 200);
delay (50);


digitalWrite(vidros_abrir, LOW);

delay (2000);
digitalWrite(piscas, LOW);

}
}
}
