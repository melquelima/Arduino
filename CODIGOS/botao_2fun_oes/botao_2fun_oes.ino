int count = 0; //variavel a receber a quantidade de pulsos
int botao = 3; 
boolean comando = true; // variavel que determina a função a ser executada
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(botao, INPUT_PULLUP);
}

void loop() {

  if (!digitalRead(botao)) {  //se o botao for pressionado
    count = 0;                //zera count
    while (!digitalRead(botao)) { // enquanto o totao estiver pressionado
      count++;             // adciona mais 1 a count
      delay(200);           // espera 200milisegundos
      if (count == 10) {    // verifica se count eigual a 10 se for
        Serial.println("led2"); //printa led2
        comando = false;       // indica que a outra função nao sera executada
        while (!digitalRead(botao)) {} // espera o usuario tirar o dedo do botao
      }
    }
    if (comando)  // se comando for igual a true
      Serial.println("led1"); //printa led1
      comando = true;   // seta comando como true
  }


}
