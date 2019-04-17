#include <mills.h>

// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0PinALast = LOW;
int n = LOW;
int SW = 7;
int lin_max = 0;
int pisca = 0;

int dataIn = 12;
int CS = 11;
int clock = 10;

int data[8]={
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


int senha[8]={
  0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};


mills tempo(300);

void setup() {
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(CS,   OUTPUT);

  pinMode (encoder0PinA,INPUT);
  pinMode (encoder0PinB,INPUT);
  pinMode (SW,INPUT_PULLUP);


  Serial.begin(9600);
  digitalWrite(CS,0);

  max7219_init();
  tempo.inicio();
  // attachInterrupt(1, encoder, RISING);
}

void loop() {
  n = digitalRead(encoder0PinA);
  if (!encoder0PinALast && digitalRead(encoder0PinA) && lin_max != 8){
    if (digitalRead(encoder0PinB))right(); 
    else  left();


    Serial.print (data[lin_max]);
    Serial.print ("/");
    if (lin_max != 8)draw(data);
  } 
  encoder0PinALast = n;

  if(!digitalRead(SW)){
    lin_max++;
    lin_max = (lin_max >8?0:lin_max);
    //Serial.print(lin_max);
    draw(data);
    while(!digitalRead(SW));
  }

  if(tempo.verifica() && lin_max !=8){
    byte a = data[lin_max];
    byte val = (pisca ==0?(data[lin_max]==255?0:(data[lin_max]<<1))|a:
    (data[lin_max] == 0x00?data[lin_max]+1:data[lin_max]));
    max_write(lin_max+1,(pisca ==0?(data[lin_max]==255?0:val):
    (data[lin_max]==255?data[lin_max]:val)));
    pisca = !pisca;
    Serial.println ((data[lin_max]==255?0:1),DEC);  
  }
  
  if (password()){
   Serial.println("SENHA OK"); 
  }

}


boolean password(){
 for(int i = 0;i<8;i++){
  if (senha[i] != data[i])return false;
 } 
 return true;
}

void left(){
  byte a = data[lin_max];
  data[lin_max] = (millis()>2000?(data[lin_max]<<1)|a:data[lin_max]);
  data[lin_max] = (data[lin_max]>255?255:data[lin_max]);
  data[lin_max] = (data[lin_max]==0?1:data[lin_max]);
  Serial.println("<");

}

void right(){
  byte a = data[lin_max];
  data[lin_max] = (data[lin_max]>>1);
  data[lin_max] = (data[lin_max]<0?0:data[lin_max]);
  Serial.println(">"); 
}



void pulseCS(){    //função responsavel por dar o pulso no CS que por sua vez envia o byte enviado
  digitalWrite(CS,1);
  delay(1);
  digitalWrite(CS,0);
}

void max7219_init(){
  shiftOut(dataIn, clock, MSBFIRST, max7219_reg_decodeMode);
  shiftOut(dataIn, clock, MSBFIRST, 0x00);
  pulseCS();
  shiftOut(dataIn, clock, MSBFIRST, max7219_reg_intensity);
  shiftOut(dataIn, clock, MSBFIRST, 0x02); 
  pulseCS();
  shiftOut(dataIn, clock, MSBFIRST, max7219_reg_scanLimit);
  shiftOut(dataIn, clock, MSBFIRST, 0x07);  
  pulseCS();
  shiftOut(dataIn, clock, MSBFIRST, max7219_reg_shutdown);
  shiftOut(dataIn, clock, MSBFIRST, 0x01);  
  pulseCS();
  shiftOut(dataIn, clock, MSBFIRST, max7219_reg_noop);
  shiftOut(dataIn, clock, MSBFIRST, 0x01);  
  pulseCS();



  for (int i =1;i<=8;i++){ //varredura dos 8 digitos
    shiftOut(dataIn, clock, MSBFIRST, i);
    shiftOut(dataIn, clock, MSBFIRST, 0);
    pulseCS(); //hablita o comando
  }

}


void max_write(int lin, int data){
  shiftOut(dataIn, clock, MSBFIRST, lin);
  shiftOut(dataIn, clock, MSBFIRST, data);
  pulseCS(); //hablita o comando 
}


void draw(int* desenho){
  for(int i =1;i<9;i++){
    max_write(i,desenho[i-1]); 
  }

}








