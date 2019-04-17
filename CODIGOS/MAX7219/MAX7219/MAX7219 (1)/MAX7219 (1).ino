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


int dataIn = 12;
int CS = 11;
int clock = 10;

void setup() {
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(CS,   OUTPUT);
  digitalWrite(CS,0);
  max7219_init();

draw(squar);
  //for(int i = 0;i<=255;i++){
  //    max_write(2,i);
  //  delay(50);
 // }
    //    max_write(1,1);
   // delay(100);
  
}

void loop() {
  // put your main code here, to run repeatedly: 

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


