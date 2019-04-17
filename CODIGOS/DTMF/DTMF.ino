#define RELE1 2 // Conectado ao fio branco do módulo Relé(Figura4)

#define pinBit01  7 // Q0
#define pinBit02  6 // Q1
#define pinBit03  5 // Q2
#define pinBit04  4 // Q3
#define pinBitStd 3 // STD

int tecla = 0;      // Variavel que vai receber o valor convertido das portas BITS em numeros

int bit01 = 0;   // Variaves que receberão "1" (HIGH) ou "0" (LOW)     
int bit02 = 0; 
int bit03 = 0; 
int bit04 = 0; 
int bitStd= 0; 

int RELE1_STATE = LOW; // Estado do Relé LOW (Desligado)

void setup() { 
  Serial.begin(9600); // Iniciamos a Serial com 9600
  pinMode(RELE1, OUTPUT); // Definimos o pino do Relé como Saída
  Serial.println("Aguardando tecla de comando..."); // Exibimos a mensagem no terminal...
}

void loop(){ 

  bitStd = digitalRead(pinBitStd); //Lê o estado do pino STD e armazena em 'bitStd' 

  if (bitStd == HIGH) {//Se estiver em nível alto fará as leituras 
                       //dos bits dos pinos Q3, Q2, Q1 e Q0

    bit01 = digitalRead(pinBit01);   
    bit02 = digitalRead(pinBit02); 
    bit03 = digitalRead(pinBit03); 
    bit04 = digitalRead(pinBit04); 

    tecla = (bit04 * 8) + (bit03 * 4) + (bit02 * 2) + (bit01 * 1);//Conversão binária para 
                                                                  //decimal (ver Vídeo1)

    Serial.print("Recebido: "); // Exibe a mensagem

    switch (tecla){ // Seleciona a tecla pressionada

    case 1: // Tecla 1
      Serial.println("1");     
      /* COMANDO PARA RELE1 */
      RELE1_STATE = !RELE1_STATE; // Guarda o estado INVERTIDO do Relé.     
      break;

    case 2: // Tecla 2
      Serial.println("2");               
      break;

    case 3: // Tecla 3
      Serial.println("3");
      break;

    case 4: // Tecla 4
      Serial.println("4");
      break;

    case 5: // Tecla 5
      Serial.println("5");
      break;

    case 6: // Tecla 6
      Serial.println("6");
      break;

    case 7: // Tecla 7
      Serial.println("7");
      break;

    case 8: // Tecla 8
      Serial.println("8");
      break;

    case 9: // Tecla 9
      Serial.println("9");
      break;

    case 10: // Tecla 0
      Serial.println("0");
      break;

    case 11: // Tecla *
      Serial.println("*");
      break;

    case 12: // Tecla #
      Serial.println("#");
      break; 
    }

    digitalWrite(RELE1, RELE1_STATE);//Liga ou desliga o Relé1 conforme o estado (HIGH/ LOW)

    // Zeram-se todas as variáveis 
    tecla = 0;
    bit01 = 0;   
    bit02 = 0; 
    bit03 = 0; 
    bit04 = 0; 
    bitStd= 0; 
    delay (500); // Aguarda 500 milissegundos
  } // Sai do switch
} // Volta pro loop...
