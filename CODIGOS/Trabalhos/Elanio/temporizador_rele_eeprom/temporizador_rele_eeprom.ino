#include <EEPROM.h>             //inclui biblioteca EEPROM
#include <mills.h>             //inclui biblioteca mills

#define SIZE 3                                  //Quantidade de reles
int reles[SIZE]={13,12,11};                     // portas onde os reles estao ligados
int eeprom [SIZE][2]={{1,1},{2,2},{4,4}};       //tempos de cada rele {tempo_ligado,tempo_desligado}

struct MyObject {                            //Objeto de cada rele contem a porta que esta ligado e seus respectivos tempos
  int rele;
  int tempo_ligado;
  int tempo_desligado;
};

MyObject rele_obj[SIZE];                     // Array de objetos referente a quantidade de reles em funcionamento

mills tempos[SIZE];                          //Array de tempo este array que ira fazer o controle de tempo de todos os reles

void setup() {
  Serial.begin(9600);                      //inicialização da serial

  for(int i = 0,j=0;i<SIZE;i++,j=j+2){    //For responsavel por gravar os valores do array 'eeprom' na eeprom
    if(EEPROM.read(j) != eeprom[i][0]){
      EEPROM.write(j,eeprom[i][0]);
      Serial.println("gravou");
    }
    if(EEPROM.read(j+1) != eeprom[i][1]){
      EEPROM.write(j+1,eeprom[i][1]);
      Serial.println("gravou");
    }
  }


  Serial.println("Lendo informacoes");
  for(int i = 0,j=0;i<SIZE;i++,j=j+2){                     //for responsável por ler as configurações da eeprom e setar os reles como saída
    pinMode(reles[i], OUTPUT);
    rele_obj[i].rele = reles[i];                          //Insere valor nos respectivos objetos de cada rele
    rele_obj[i].tempo_ligado = EEPROM.read(j);            //Insere valor nos respectivos objetos de cada rele
    rele_obj[i].tempo_desligado = EEPROM.read(j+1);       //Insere valor nos respectivos objetos de cada rele
    Serial.print("Rele ");
    Serial.print(i);
    Serial.print(" - T_Ligado:");
    Serial.print(rele_obj[i].tempo_ligado);
    Serial.print("s - T_Desligado:");
    Serial.print(rele_obj[i].tempo_desligado);
    Serial.println("s");

    tempos[i].setTime((digitalRead(rele_obj[i].rele)?rele_obj[i].tempo_ligado:rele_obj[i].tempo_desligado)*1000); // responsável por setar os tempos iniciais de cada rele conforme o estado atual do mesmo (ligado ou desligado)
    tempos[i].on();                                                                                              // responsável por inicializar os timers(iniciar contagem)
  }

}

void loop() {
  for(int i = 0;i<SIZE;i++){                                                       //for que percorre todos os objetos rele_obj
    int on_off = digitalRead(rele_obj[i].rele);                                    //status atual do rele atual
    int temp = (on_off?rele_obj[i].tempo_desligado:rele_obj[i].tempo_ligado);      //proximo tempo do rele em relação ao seu status
    if(tempos[i].verifica()){                                                      //verifica se o tempo estimado do rele atual foi atingido
      digitalWrite(rele_obj[i].rele,!on_off);                                      //muda o status do rele atual
      tempos[i].setTime(temp*1000);                                                //configura o proximo tempo do rele atual 
      tempos[i].reset();                                                           //reinicia o tempo de contagem do rele atual
    }
  }


}



