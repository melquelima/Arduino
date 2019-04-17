#include <EEPROM.h>
int portas[8] = {3, 4, 5, 6, 8, 9, 10, 11};
//os 4 primeiros numeros para linhas
//os 4 ultimos numeros para colunas

String senha;
String digitado;
int dig = 0;
char letras[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void setup()
{
  for (int i = 0; i < 4; i++)
    pinMode(portas[i], OUTPUT);

  for (int i = 4; i < 8; i++)
    pinMode(portas[i], INPUT);

  Serial.begin(9600);
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println("digite a senha com 5 caracteres");
  Serial.println();
  pega_senha();

}

void loop()
{
  verifica_tecla();
  if (dig == 5) {
    if (senha == digitado) {
      Serial.println("Senha correta");
      delay(2000);
      Serial.println("Digite a senha");
    } else {
      Serial.println("Senha incorreta");
      delay(2000);
      Serial.println("Digite a senha");
    }
    dig = 0;
    digitado = "";
  }
}

void verifica_tecla() {
  for (int ti = 0; ti < 4; ti++)
  {
    //Alterna o estado dos pinos das linhas
    for (int i = 0; i < 4; i++)
      digitalWrite(portas[i], LOW);

    digitalWrite(portas[ti], HIGH);
    //Verifica se alguma tecla da coluna 1 foi pressionada
    if (digitalRead(portas[4]))// se o botao for pressionado
    {
      concatena(ti + 1, 1);
      while (digitalRead(portas[4])) {}
    }

    //Verifica se alguma tecla da coluna 2 foi pressionada
    if (digitalRead(portas[5]))
    {
      concatena(ti + 1, 2);
      while (digitalRead(portas[5])) {};
    }

    //Verifica se alguma tecla da coluna 3 foi pressionada
    if (digitalRead(portas[6]))
    {
      concatena(ti + 1, 3);
      while (digitalRead(portas[6])) {}
    }

    //Verifica se alguma tecla da coluna 4 foi pressionada
    if (digitalRead(portas[7]))
    {
      concatena(ti + 1, 4);
      while (digitalRead(portas[7])) {}
    }
  }
  delay(10);
}


void concatena(int L, int C)
{
  if (L == 1 && C == 4) {
    configura_senha();
    dig = 0;
    digitado = "";
  } else {
    Serial.println(letras[L - 1][C - 1]);
    digitado = digitado + letras[L - 1][C - 1];
    dig++;
  }
}

void configura_senha() {
  Serial.println("Digite a nova senha");

  while (dig != 6) {
    verifica_tecla();
    if (dig == 5) {
      char sen[6];
      digitado.toCharArray(sen,6);
      
      EEPROM.write(6,sen[0]);
      EEPROM.write(7, sen[1]);
      EEPROM.write(8, sen[2]);
      EEPROM.write(9, sen[3]);
      EEPROM.write(10, sen[4]);

      dig = 6;
      digitado = "";
      Serial.println("Senha Configurada");
      dega_senha();
    }
  }
}

void pega_senha() {

  for (int i = 6; i < 11; i++)
    senha = senha + char(EEPROM.read(i));
  Serial.println(senha);
}
