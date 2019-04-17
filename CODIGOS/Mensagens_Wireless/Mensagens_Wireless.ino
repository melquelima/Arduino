#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x38,20,4);

uint8_t letter[8] = {0x0,0x0,0x1f,0x1b,0x15,0x11,0x1f,0x0};
uint8_t nm_0[8] = {0x1f,0x18,0x14,0x12, 0x11, 0x10, 0x10, 0x1f};
byte nm_1[8] = {B11111,B00011,B00101,B01001,B10001,B00001,B00001,B11111};
uint8_t estrut[8] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,};
byte esq[8] = {B00010,B00110,B01110,B11110,B11110,B01110,B00110,B00010};
byte dir[8] = {B01000,B01100,B01110,B01111,B01111,B01110,B01100,B01000};

String mensagens[10]={};
int count;
int quantidade;
int vld_msg=0;
int atual;

void setup(){
Serial.begin(9600); 
lcd.init();
lcd.clear();
lcd.createChar(0, letter);
lcd.createChar(1, nm_0);
lcd.createChar(2, nm_1);
lcd.createChar(3, estrut);
lcd.createChar(4, esq);
lcd.createChar(5, dir);
lcd.home();
verifica();
estrutura();

pinMode(12,INPUT);
pinMode(11,INPUT);
pinMode(10,INPUT);
}

void loop(){
  
  if(Serial.available()>0){
   String msg_receive = Serial.readString();
   guarda(msg_receive);
  }
  if(digitalRead(12)){
   if(exist_msg())
   if(vld_msg != quantidade){
   vld_msg++;
    escreve(mensagem_return()); 
    delay(10);
   }
  }
    if(digitalRead(11)){
      if(vld_msg ==1){vld_msg=0;lcd.clear();estrutura();verifica();
      }
      if(vld_msg !=1 && vld_msg !=0){
      vld_msg--;
      escreve(mensagem_return());
      delay(10);
      }
    }
  if(digitalRead(10)){
   if(vld_msg != 0)
    del(); 
  }
  
}


void verifica(){
  for(int i =0; i<10;i++)
  count += (mensagens[i] !=""?1:0);
  lcd.setCursor(18,0);
 lcd.print(ArrumaZero(count));
 quantidade = count;
  count=0; 
}


void guarda(String msg){
for(int i =0; i<10;i++)
if(mensagens[i] == ""){
  mensagens[i]=msg;
 verifica();
  return;
}
}



void estrutura(){
  
  lcd.setCursor(16,0);
  lcd.write(1);
  lcd.setCursor(17,0); 
  lcd.write(2);
  
  
  for (int i=0;i<4;i++){
  lcd.setCursor(0,i);
  lcd.write(3);
  }
  for (int i=0;i<4;i++){
  lcd.setCursor(13,i);
  lcd.write(3);
  }
  lcd.setCursor(14,3);
  lcd.write(4);
  lcd.setCursor(16,3);
  lcd.print("DT");
  lcd.setCursor(19,3);
  lcd.write(5);
  lcd.setCursor(15,2);
  lcd.print("[00]");
 
}

void escreve(int numm){
  limpa();
  String str = mensagens[numm];
  int tamanho = str.length()+1;
  char letras[tamanho];
  str.toCharArray(letras,tamanho);
  int numero_casas=0;
  int carac = 0;
  
  for(int j=0;j<4;j++){
  carac +=12;
  for(int i=1;i<=12;i++){
   lcd.setCursor(i,j);
    numero_casas++;
    if(numero_casas < tamanho)
   lcd.print(letras[(i-1)+carac-12]); 
  }
  }
  atual = numm+1; 
 lcd.setCursor(16,2);
 lcd.print(ArrumaZero(numm+1)); 
}

String ArrumaZero(int i){
 String ret;
 if(i <10){ret += "0";} 
  ret += i;
  return ret;
  
}

boolean exist_msg()
{
 for(int i=0; i<10;i++){
   if(mensagens[i] != ""){
    return true; 
   }
 }
 return false;
}


int mensagem_return(){
  
  if(vld_msg==1)
 for(int i=0; i<10;i++){
   if(mensagens[i] != ""){
    return i; 
   }
 }
 
 return vld_msg -1;
  
}

void limpa(){
 for(int j=0;j<4;j++){
  for(int i=1;i<=12;i++){
   lcd.setCursor(i,j);
   lcd.print(" "); 
  }
  } 
}

void del(){
  int del_msg = vld_msg -1;

  for (int i=del_msg; i<=10; i++)
  {mensagens[i] = mensagens[i+1]; }
  
  estrutura();
  verifica();
  limpa();
}

