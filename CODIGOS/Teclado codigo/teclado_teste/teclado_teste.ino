#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

//int portas[8]= {13, 12, 11, 10, 7, 6, 5, 4};
int portas[4]= {7, 6, 5, 4};

//------------------------------PCF
int _end = 39;
int numero[8]={1,1,1,1,1,1,1,1};

//------------------------------TECLADO
String senha = "12345";
String digitado = "";

char letras[4][4] ={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

void setup()
{
  lcd.init();
  lcd.backlight();
for(int i =0;i<4;i++){
  pinMode(portas[i], INPUT_PULLUP);
}
Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Digite a senha:");
  lcd.blink();
  lcd.setCursor(0,1);
  //_digWrite(0,0);
  //Serial.print("valor:");
  //Serial.println(_digRead(7));
  //while(1){}

   
  
}
 
void loop()
{
  
  String tecla = verifica_tecla();
  if(tecla != ""){
    digitado += tecla;
    digitaLinha(1,digitado);
  }
  if(digitado.length() == senha.length()){    
    if(digitado == senha){
      digitaLinha(1,"Senha correta!");
    }else{
      digitaLinha(1,"Senha incorreta!");
    }
    digitado = "";
    delay(2000);
    digitaLinha(1,"");
  }
}

void digitaLinha(int linha,String texto){
    lcd.setCursor(0,linha);
    lcd.print("                ");
    lcd.setCursor(0,linha);
    lcd.print(texto);
}

 
 String verifica_tecla(){
   for(int i=0;i<4;i++){
     for(int k =0;k<4;k++){
       _digWrite(k,1);
       //digitalWrite(portas[k], 1);
     }
     _digWrite(i,0);
     //digitalWrite(portas[i], 0); //0-3
     for(int j=0;j<4;j++){
       //if (!digitalRead(portas[j])){
         if (_digRead(j+4)){
         while(_digRead(j+4)){}
         delay(100);
         return String(letras[i][j]);
       }
     }
   }
   return "";
 }
 
 void _digWrite(int pt, int valor){
     numero[pt] = valor;
        int num =
        (numero[0]*1) +     (numero[1]*2) + 
        (numero[2]*4) +     (numero[3]*8) + 
        (numero[4]*16) +    (numero[5]*32) + 
        (numero[6]*64) +    (numero[7]*128);
    
      Wire.beginTransmission(_end);
      Wire.write(num);
      Wire.endTransmission();
}
 
 int _digRead(int y){
      Wire.requestFrom(_end,1);
    if(Wire.available())  {
      byte x = Wire.read();
      //Serial.println(x,BIN);
      for (int j = 0; j <= 7; j++){
        if(!(x & (1 << j)) && y == j){
          return true;
        }
      }
      return false;
    }
}
 
