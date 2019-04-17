byte p1[8] = {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
byte p2[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
byte p3[8] = {0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C};
byte p4[8] = {0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E};
byte p5[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
int celula = 0;


int count;
int comando = true;
//-------LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(39,8,2); 
//-------MEMORIA
#include <EEPROM.h>
//--------Array onde e armazenada a senha
int senha [3] ={
  70,100,255};
//----Margem de erro 
int margem = 30;
//-----Terminais analogicos
int A = A1;
int B = A2;
int C = A3;
//-----variaves que recebem o valor analogico
int val_a;
int val_b;
int val_c;
//------Botao de menu
int btn_menu = 13;
//------Botoes de incremento e decremento
int btn_up = 6;
int btn_down = 7;
//--------Rele
int rele = 5;


void setup(){
  lcd.init();
  lcd.backlight();
    lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
  Serial.begin(9600);
  pinMode(btn_menu,INPUT);
  pinMode(btn_up,INPUT);
  pinMode(btn_down,INPUT);
  pinMode(rele,OUTPUT);
  pega_senha();
  delay(2000);

}

void loop(){
  mostra();
  val_a = analogRead(A1);
  val_b = analogRead(A2);
  val_c = analogRead(A3);
  delay(100);

  if((val_a <= senha[0]+margem && val_a >= senha[0]-margem) && (val_b <= senha[1]+margem && val_b >= senha[1]-margem) && (val_c <= senha[2]+margem && val_c >= senha[2]-margem)){
    Serial.println("OK");
    ok();
  }

  if (!digitalRead(btn_menu)) {  //se o botao for pressionado
    count = 0;                //zera count
    while (!digitalRead(btn_menu)) { // enquanto o totao estiver pressionado
      count++;             // adciona mais 1 a count
      delay(200);           // espera 200milisegundos
      if (count == 10) {    // verifica se count eigual a 10 se for
        configura_senha();
        comando = false;       // indica que a outra função nao sera executada
        while (!digitalRead(btn_menu)) {} // espera o usuario tirar o dedo do botao
      }
    }
    if (comando)  // se comando for igual a true
      confg();
      comando = true;   // seta comando como true
  }
}


void ok(){
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Ativado");
digitalWrite(rele,1);
for(int j=0;j<=7;j++)
   for(int i=1;i<=4;i++){
         lcd.setCursor(j, 1);
         lcd.write(i);
         delay((EEPROM.read(20)*1000)/40);
    }
digitalWrite(rele,0);
}

void confg(){
  int segundos=0;
  int atualiza = false;
  while(!digitalRead(btn_menu)){
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("T.rele  ");
  lcd.setCursor(0,1);
  lcd.blink();
  while(digitalRead(btn_menu)){
    if(!digitalRead(btn_up)){
      segundos ++;
      atualiza = true;
      while(!digitalRead(btn_up)){
      } 
      delay(300);
    }
    if(!digitalRead(btn_down)){
      segundos = (segundos==0?0:segundos-1);
      atualiza = true;
      while(!digitalRead(btn_down)){
      }
      delay(300); 
    }
    if(atualiza){
      atualiza = false;
      lcd.setCursor(0,1);
      lcd.print("        ");
      lcd.setCursor(0,1);
      lcd.print(segundos);
    }

  }
  while(!digitalRead(btn_menu)){
  }
  lcd.clear();
  lcd.noBlink(); 
  lcd.setCursor(0,0);
  lcd.print("===OK===");
  EEPROM.write(20,segundos);
delay(3000);  
}

void configura_senha(){

  EEPROMWritelong(0,val_a);
  EEPROMWritelong(5,val_b);
  EEPROMWritelong(10,val_c);
  Serial.println("senha gravada com sucesso");
  pega_senha();
  while(!digitalRead(btn_menu)){
    delay(100);
  }
}

void pega_senha(){
  senha[0] = EEPROMReadlong(0);
  senha[1] = EEPROMReadlong(5);
  senha[2] = EEPROMReadlong(10);
  Serial.print("A1: ");
  Serial.print(senha[0]);
  Serial.print(" A2: ");
  Serial.print(senha[1]);
  Serial.print(" A3: ");
  Serial.println(senha[2]);
}


void mostra(){
  lcd.clear();
  Serial.print("A1: ");
  Serial.print(analogRead(A));
  Serial.print(" A2: ");
  Serial.print(val_b);
  Serial.print(" A3: ");
  Serial.println(val_c);  
  lcd.setCursor(0,0);
  lcd.print(val_a);
  lcd.setCursor(4,0);
  lcd.print(val_b);
  lcd.setCursor(0,1);
  lcd.print(val_c);
}

void EEPROMWritelong(int address, long value)
{
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
long EEPROMReadlong(long address)
{
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}




