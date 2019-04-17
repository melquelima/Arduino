#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(39,16,4);  // set the LCD address to 0x20 for a 16 chars and 2 line display
AccelStepper stepper(1,5,3);
SoftwareSerial controle(8, 99); // RX, TX

int enable = 4;
int conf[4];
int red = 10;
int up = 11;
int down = 12;
int esq = 17, dir = 16;
int EMax,DMax;
int sair = 0; // codigo 0 indica que nao deve sair
int y_cima = 6,y_baixo=7,y_fim = 15;
int saida_global = 0;
int pistola_es =  9,pistola_dir = 14;


byte left[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B00111,
  B00011,
  B00001,
};

byte rigth[8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11100,
  B11000,
  B10000,
};

byte vector_up[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B01110,
  B01110,
  B00000
};

byte vector_down[8] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000
};


void setup()
{
  eeprom_conf();
  pinMode(red,INPUT_PULLUP);
  pinMode(up,INPUT_PULLUP);
  pinMode(down,INPUT_PULLUP);
  pinMode(esq,INPUT);
  pinMode(dir,INPUT);
  pinMode(y_cima,OUTPUT);
  pinMode(y_baixo,OUTPUT);
  pinMode(y_fim,INPUT_PULLUP);
  pinMode(enable,OUTPUT);
  pinMode(pistola_es,OUTPUT);
  pinMode(pistola_dir,OUTPUT);
  digitalWrite(enable,1);
  //attachInterrupt(0, alarme, RISING); 
  Serial.begin(9600);
  controle.begin(9600);
  lcd.init();  
  lcd.backlight();
  lcd.createChar(1,left);
  lcd.createChar(2,rigth);
  lcd.createChar(3,vector_up);
  lcd.createChar(4,vector_down);


  esquerda();
  delay(1000);
  direita();
  principal();
}
// 0 pressionado
// 1 segurado
// 2 nada pressionado

void motor(){
  int sped = conf[1]*100;
  stepper.setMaxSpeed(sped);
  stepper.setAcceleration(sped);
  stepper.setSpeed(sped);

  Serial.print("speed --- ");
  Serial.println(sped);
}
void motor2(){
  int sped = 2000;
  stepper.setMaxSpeed(sped);
  stepper.setAcceleration(sped);
  stepper.setSpeed(sped);

  Serial.print("speed --- ");
  Serial.println(sped);
}



void loop()
{
  if(reed()==1){
    menu();
    principal();
  }
  if(controle.available()){
    int comando = controle.read();
//=============================================
    if(comando == '%'){ // comando AUTOMÁTICO
      automatico();
    }
//============================================
    if(comando == '<'){  // comando MANUAL
      motor2();
      
      while(controle.read() != '!'){
        stepper.moveTo(stepper.currentPosition()-80);
        stepper.runSpeedToPosition();
   //     Serial.println("<");
      }
    }
 //=========================================
    if(comando == '>'){  // comando MANUAL
      motor2();
      while(controle.read() != '!'){
        stepper.moveTo(stepper.currentPosition()+80);
        stepper.runSpeedToPosition();
      }    }
//=========================================
if(comando == 'c' || comando == 'b'){
  digitalWrite((comando == 'c'?y_cima:y_baixo),1);
    while(controle.read() != '!'){}
      digitalWrite((comando == 'c'?y_cima:y_baixo),0);
}
   
  }

}

void x_esquerda(){
  motor();
  int saida = controle.read();
  while((stepper.currentPosition() != EMax) && (saida != 's')){
    saida = controle.read();
    stepper.moveTo(stepper.currentPosition()-50);
    stepper.runSpeedToPosition();
  }
  if(saida == 's'){
   saida_global = 1; 
  }
}

void x_direita(){
  motor();
  int saida = controle.read();
  while((stepper.currentPosition() != DMax) && (saida != 's')){
    saida = controle.read();
    stepper.moveTo(stepper.currentPosition()+50);
    stepper.runSpeedToPosition();
  }
   if(saida == 's'){
   saida_global = 1; 
  } 
}

void automatico(){
  Serial.println("PONTO INICIAL");
  x_direita(); //inicia sempre na direita
int vez = 0;
    while(digitalRead(y_fim) && saida_global != 1){
    for(int i= 1;i<=conf[0];i++){
      if(vez == 0){
        Serial.println("<<<<");
        digitalWrite(pistola_es,1);
        x_esquerda();
        digitalWrite(pistola_es,0);
        vez = 1;
      }
      else{
        Serial.println(">>>>");
        digitalWrite(pistola_dir,1);
        x_direita();
        digitalWrite(pistola_dir,0);
        vez = 0;
      }
      if(saida_global == 1){
       exit; 
      }
    }
    digitalWrite(pistola_es,0);
    digitalWrite(pistola_dir,0);
    if(saida_global != 1){
    y();
    }
  }
  if(saida_global == 1){

    saida_global = 0;
    Serial.println("=======SAIDA========"); 
  }

}

void y(){

  int tempo = (conf[2]<0?(conf[2]*(-1))*100:conf[2]*100);
  Serial.println(tempo);
  if(conf[3]==1){ // vai para cima
  Serial.println("++++");
    digitalWrite(y_cima,1);
    for(int i=1;i<=tempo;i++){
    delay(1);
    if(controle.read() == 's' || !digitalRead(y_fim)){
      digitalWrite(y_cima,0);
      saida_global = 1;
      return;
    }
    }
    digitalWrite(y_cima,0);
  }
  else{ // vai para baixo
  Serial.println("----");
    digitalWrite(y_baixo,1);
    for(int i=1;i<=tempo;i++){
    delay(1);
    if(controle.read() == 's'){
      digitalWrite(y_baixo,0);
      saida_global = 1;
      return;
    }
    }
    digitalWrite(y_baixo,0);    
  }



}

void alarme(){
  sair = 1; // codigo 1 indica a saida por alarme
  Serial.println("OK");
  Serial.println(sair);
}

void principal(){
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.print(EMax);
  lcd.setCursor(0,1);
  lcd.write(2);
  lcd.print(DMax); 
}

void esquerda(){  
  Serial.println("Configurando esquerda....");
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.print("...");  
  stepper.setMaxSpeed(1600);
  stepper.setAcceleration(2000);
  stepper.setSpeed(1600);  
  while((!digitalRead(esq)) && (controle.read() != 's')){   /* && sair != 1*/
    stepper.moveTo(stepper.currentPosition()-50);
    stepper.runSpeedToPosition();
  }
  if(sair != 1){
    stepper.moveTo(stepper.currentPosition());
    stepper.runSpeedToPosition();
    EMax = stepper.currentPosition();
    Serial.println("====Esquerda configurada====");
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("=====ALARME=====");
    detachInterrupt(0); 
    while(1){
      controle.println("!"); // comando de ALARME
    };
  }
}


void direita(){  
  Serial.println("Configurando direita....");
  lcd.setCursor(0,1);
  lcd.write(2);
  lcd.print("...");  
  stepper.setMaxSpeed(1600);
  stepper.setAcceleration(2000);
  stepper.setSpeed(1600);  
  while((!digitalRead(dir)) && (controle.read() != 's')/*&& sair != 1*/){
    stepper.moveTo(stepper.currentPosition()+50);
    stepper.runSpeedToPosition();
  }
  if(sair != 1){
    stepper.moveTo(stepper.currentPosition());
    stepper.runSpeedToPosition();
    DMax = stepper.currentPosition();
    Serial.println("====Direita configurada====");
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("=====ALARME====="); 
    detachInterrupt(0);
    while(1){
      controle.println("!"); // comando de ALARME
    };  
  }
}

void menu(){
  int atual =1;

  estrutura();
  lcd.setCursor(5,atual);
  lcd.cursor();
  int estado = 2; // nenhum botão pressionado

  while(estado != 1){
    estado = reed();
    Serial.println(estado);
    if(estado==0){
      atual = (atual==1?3:atual-1);
      lcd.setCursor((atual==1?5:1),atual);
    }

    //=====UP
    for (int i=1;i<=3;i++)
      if(!digitalRead(up) && atual == i){
        conf[i-1]  = (i==1?(conf[i-1]>8?9:conf[i-1]+1):
        conf[i-1]+1);
        estrutura();
        lcd.setCursor((atual==1?5:1),atual);
        lcd.cursor();
        while(!digitalRead(up));
        delay(50);  
      }

    // =======DOWN
    for (int i=1;i<=3;i++)
      if(!digitalRead(down) && atual == i){
        conf[i-1]  = (i!=3?(i==1?(conf[i-1]<2?1:conf[i-1]-1):
        (conf[i-1]<2?1:conf[i-1]-1)):
        conf[i-1]-1);
        estrutura();
        lcd.setCursor((atual==1?5:1),atual);
        lcd.cursor();
        while(!digitalRead(down));
        delay(50);  
      }
  }

  lcd.clear();
  lcd.noCursor();
  grava();
  eeprom_conf();
}

void grava(){
  EEPROM.write(1,conf[0]);
  EEPROM.write(2,conf[1]);
  EEPROM.write(3,(conf[2]<0?conf[2]*-1:conf[2]));
  EEPROM.write(4,(conf[2]<0?1:2));
}
void eeprom_conf(){
  conf[0] = EEPROM.read(1);
  conf[1] = EEPROM.read(2);
  conf[2] = EEPROM.read(3);
  conf[3] = EEPROM.read(4);
  conf[2] = (conf[3] ==1? conf[2]*-1:conf[2]);
}

int reed(){
  int count;

  if (digitalRead(red)){
    return 2;
  }

  if (!digitalRead(red)) {  //se o botao for pressionado
    count = 0;                //zera count
    while (!digitalRead(red)) { // enquanto o totao estiver pressionado
      count++;             // adciona mais 1 a count
      delay(100);           // espera 200milisegundos
      if (count == 10) {    // verifica se count eigual a 10 se for
        lcd.setCursor(15,1);
        lcd.print("*");
        while (!digitalRead(red)) {
        } // espera o usuario tirar o dedo do botao
        delay(100);
        return 1;      
      }
    }
    return 0;
  }


}


void estrutura(){
  //=======ESTRUTURA================
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("======MENU======");
  lcd.setCursor(4,1);
  lcd.print("(");
  lcd.print(conf[0]);
  lcd.print(")Demao");
  lcd.setCursor(0,2);
  lcd.print("(");
  lcd.print(conf[1]);
  lcd.print(")Vel");
  lcd.setCursor(0,3);
  lcd.print("(");
  lcd.print(conf[2]);
  lcd.print(")Desloc ");
  lcd.write((conf[2]<0?4:3));
}





















