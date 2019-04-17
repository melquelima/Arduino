#include <LiquidCrystal.h>
#include <mills.h> // UTILIZAÇÃO DE MILLIS
#include <EEPROM.h> // UTILIZAÇÃO DA EEPROM PARA GUARDAR VALORES
mills tempo_S1(0);  //CONTROLA O TEMPO DE ESPERA DO S1
mills tempo_S2(0);  //CONTROLA O TEMPO DE ESPERA DO s2
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

int MenuBut = 10; // BOTAO DE MUDANÇA DE TELA
int Up = 9;      // BOTAO DE ADIÇAO
int Dw = 8;      // BOTAO DE DECREMENTO
int tela = 0;    // CONTROLE DE TELA ATUAL
int C_CICLO = 0;  // CONTATEM DE CICLO
int C_MULT = 0;  //CONTADEM DE MULTIPLICADOR
int CICLO = 2;//EEPROM.read(10);      //VALOR ATUAL DO CICLO
int MULT = 3;//EEPROM.read(20);       //VALOR ATUAL DA MULTIPLICADOR
int S1_MS = 1000;//EEPROM.read(30)*100;    //TEMPO DE ATIVAÇÃO DA S1
int S2_MS = 1000;//EEPROM.read(40)*100;    //TEMPO DE ATIVAÇÃO DA S2

int S1 = A1;  //PORTA DO S1
int S2 = A2;  //PORTA DO S2
int SensorParada = A3;

int pin = 3;

boolean S_S1 = false;
boolean S_S2 = false;

void setup() {
   //================== CONFIGURAÇÃO DO LCD ======================
  lcd.begin(16, 2);
   //==================== CONFIGURAÇÃO DA INTERRUPÇÃO DO CONTADOR ================ 
   attachInterrupt(0, Count, FALLING);
   //==================== CONFIGURAÇÃO DAS PORTAS ========================
  pinMode(MenuBut,INPUT_PULLUP);
  pinMode(Up,INPUT_PULLUP);
  pinMode(Dw,INPUT_PULLUP);
  pinMode(pin,INPUT_PULLUP);
  pinMode(SensorParada,INPUT_PULLUP);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
   //================= CONFIGURAÇÃO DO NOVO LOOP =============
  
  menuTela(tela);
  atualizaTela(tela);
  
  //================== CONFIGURAÇAO DOS TEMPOS ================
  tempo_S1.setTime(S1_MS);
  tempo_S2.setTime(S2_MS);
  tempo_S1.off();
  tempo_S2.off();
}

void loop() {
   atualiza();
 //================== VERIFICA SE O CICLO ATINGIU O LIMITE E ATIVA O TEMPO  
  if(C_CICLO == CICLO && !S_S1){
    digitalWrite(S1,1);
    tempo_S1.reset();
    tempo_S1.on();
    C_CICLO = 0;
    S_S1 = true;
    atualizaTela(tela);
  }
   //================== TEMPO DO CICLO RESPONSAVEL POR ATIVAR A PORTA NO DETERMINADO TEMPO E DESLIGA-LA
  if(tempo_S1.verifica() || !digitalRead(SensorParada)){
    digitalWrite(S1,0);
    tempo_S1.off();
    S_S1 = false;
    atualizaTela(tela);
  }
 //================== VERIFICA SE O MULTIPLICADOR ATINGIU O LIMITE E ATIVA O TEMPO  
  if(C_MULT == MULT && !S_S2){
    digitalWrite(S2,1);
    tempo_S2.reset();
    tempo_S2.on();
    C_MULT = 0;
    S_S2 = true;
    atualizaTela(tela);
  }
   //================== TEMPO DO MULTIPLICADOR RESPONSAVEL POR ATIVAR A PORTA NO DETERMINADO TEMPO E DESLIGA-LA
  if(tempo_S2.verifica()){
    digitalWrite(S2,0);
    tempo_S2.off();
    S_S2 = false;
    atualizaTela(tela);
  }
  
  if(!digitalRead(pin)){
    //Count();
    while(!digitalRead(pin)){delay(200);}
  }
}

//======================== CONFIGURAÇAO DE CONTAGEM DO SENSOR POR INTERRUPÇÃO
void Count(){
  C_CICLO = (C_CICLO == CICLO?1:C_CICLO+1);
  C_MULT = (C_CICLO == CICLO?(C_MULT==MULT?1:C_MULT+1):C_MULT);
  atualizaTela(tela);
}

//======================== CONFIGURAÇAO DE NOVO LOOP
void atualiza(){
  interacao(tela);
  if(!digitalRead(MenuBut)){
    tela = (tela==4?0:tela+1);
    menuTela(tela);
    atualizaTela(tela);
    while(!digitalRead(MenuBut)){delay(200);}
  }
}
//======================== CONFIGURAÇAO DE INTERAÇAO DE CADA TELA
void interacao(int x){
  char acao = pressionado();
  if(acao == ' '){return;}
 if(x>0){
   lcd.setCursor(0, 1);
   lcd.print("                ");
 }
 switch(x){
   //NAO FAZ NADA NA TELA PRINCIPAL
   case 0: break;
   // INTERAGE COM OS BOTOES PARA MUDAR O VALOR DO CICLO
   case 1:if(acao == 'U'){CICLO++;}else{CICLO--;}EEPROM.write(10,CICLO);break;
   // INTERAGE COM OS BOTOES PARA MUDAR O VALOR DO MULTIPLICADOR
   case 2:if(acao == 'U'){MULT++;}else{MULT--;}EEPROM.write(20,MULT);break;
   // INTERAGE COM OS BOTOES PARA MUDAR O VALOR DO TEMPO DO S1
   case 3:if(acao == 'U'){S1_MS+=100;}else{S1_MS-=100;}EEPROM.write(30,S1_MS/100);break;
   // INTERAGE COM OS BOTOES PARA MUDAR O VALOR DO TEMPO DO S2
   case 4:if(acao == 'U'){S2_MS+=100;}else{S2_MS-=100;}EEPROM.write(40,S2_MS/100);break;
 }
  tempo_S1.setTime(S1_MS);
  tempo_S2.setTime(S2_MS);
 atualizaTela(tela); //ATUALIZA A TELA
}

//======================== RETORNA SE O UP OU DOWN FOI PRESSIONADO
char pressionado(){
  char botao = ' ';
  if(!digitalRead(Up) || !digitalRead(Dw)){
    botao = (!digitalRead(Up)?'U':(!digitalRead(Dw)?'D':' '));
    while(!digitalRead(Up) || !digitalRead(Dw)){delay(200);}
  }
 return botao;
}

//======================== CONFIGURAÇÃO DE ATUALIZAÇÃO DE VALORES EM TELA
void atualizaTela(int x){
  switch(x){
   case 0:
     printLcd("    ",4,0);
     printLcd(String(C_CICLO),4,0);
     printLcd("    ",14,0);
     printLcd(String(C_MULT),13,0);
     printLcd("    ",4,1);
     printLcd((digitalRead(S1)?"ON":"OFF"),4,1);
     printLcd("    ",14,1);
     printLcd((digitalRead(S2)?"ON":"OFF"),13,1);
   break;
   case 1:printCenter(String(CICLO),1);break;
   case 2:printCenter(String(MULT),1);break;
   case 3:printCenter(String(S1_MS),1);break;
   case 4:printCenter(String(S2_MS),1);break;
 } 
}

//======================== MOSTRA A ESTRUTURA DO MENU ATUAL EM TELA
void menuTela(int x){
 lcd.clear();
  switch(x){
    case 0:
      printLcd("Clc:",0,0);
      printLcd("Mlt:",9,0);
      printLcd("S1 :",0,1);
      printLcd("S2 :",9,1);
    break;
    case 1:printCenter("Ciclo",0);break;
    case 2:printCenter("Multiplicador",0);break;
    case 3:printCenter("S1(ms)",0);break;
    case 4:printCenter("S2(ms)",0);break;
 } 
}
//======================== FUNCAO PARA ESCREVER NO LCD
void printLcd(String texto,int a,int b){
  lcd.setCursor(a, b);
  lcd.print(texto);
}
//======================== FUNCAO PARA ESCREVER NO MEIO DO LCD
void printCenter(String texto,int a){
  lcd.setCursor((16-texto.length())/2, a);
  lcd.print(texto);
}

