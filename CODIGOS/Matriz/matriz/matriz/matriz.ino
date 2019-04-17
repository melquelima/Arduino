// Este código de exemplo tem como função pegar um numero de ATÉ 4 caracteres(inseridos pelo teclado matricial)
// e converte para um numero inteiro sendo assim possivel utilizar este numero para diversar aplicações
// o numero e retornado pea função VALOR que espera o caracter # ser pressionado para que possa retornar o valor digitado
// https://www.facebook.com/noobtronick/
// Creditos: Melque Apolinario, qualquer dúvida melque_ex@yahoo.com.br

#include <Keypad.h>

const byte Coluna = 3;
const byte Linha = 4;

//==================CONFIGURAÇOES PADRAO DO TECLADO===========================
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//==============================================================================


void setup()
{
  Serial.begin(9600);
}


int fator[4] = {1000, 100, 10, 1}; // fator multiplicador de cada digito U D C M
int caracteres_digitados[4]={0,0,0,0};

void loop() {
  
      Serial.print("digite o angulo do servo :");
      Serial.println(valor());
}


int valor(){
  //lcd.setCursor(0, 0);
  //lcd.print("DIGITE O ANGULO");
  int digito = -1;
  int angulo = 0;
  boolean sai = false; // variavel que aguarda a saida do programa "ENTER"

  while (!sai) {// aquarda ser digitado todos os numeros
    char teclaPressionada = keypad.getKey();//ler a tecla pressionada
    if (teclaPressionada != NO_KEY) { //verifica se foi pressionada alguma tecla
      if (teclaPressionada != '*' && teclaPressionada != '#') { //verifica se a tecla pressionada é diferente de * e # (uma dessas teclas sera a tecla "ENTER")
      digito++; // informamos o numero de digitos inserido
     //Serial.print(digito); 
      Serial.print("digitado: ");
        //lcd.setCursor(digito, 1);
        //lcd.print(teclaPressionada); // mostramos o valor no lcd
           caracteres_digitados[digito] = teclaPressionada-48; //neste ponto estamos apenas guardando cada valor digitado no array 
            Serial.println(caracteres_digitados[digito]);
      }else{
        if (teclaPressionada == '#'){sai = true; // se a tecla pressionada for IGUAL a # sai do while e executa no servo
       // primeiro temos que saber quantos caracteres foram digitados para sabermos por que casa decimal vamos começar
      // angulo = caracteres_digitados[]
       int i,j;
       for(i = digito, j = 3; i>=0,j>=0 ;i--,j--){ //digito ==3 para 245 portando inicia em posição 2 que devera ser centena 
         angulo = angulo + caracteres_digitados[i] * fator[j];
         if (i == 0) break;    
       }
        // aqui sera executado o valor no servo
        caracteres_digitados[0] = 0;
        caracteres_digitados[1] = 0;
        caracteres_digitados[2] = 0;
        caracteres_digitados[3] = 0;
        return angulo;
        }      
      }
    }
  }
}
