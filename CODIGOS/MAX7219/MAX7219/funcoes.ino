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

void max_write(int lin, int data){
  shiftOut(dataIn, clock, MSBFIRST, lin);
  shiftOut(dataIn, clock, MSBFIRST, data);
  pulseCS(); //hablita o comando 
}


void draw(byte* desenho){
for(int i =1;i<9;i++){
 max_write(i,desenho[i-1]); 
}
  
}

void max7219_init(){
max_write(max7219_reg_decodeMode,0xff);
  max_write(max7219_reg_intensity,0x08);
  max_write(max7219_reg_scanLimit,0x07);
  max_write(max7219_reg_shutdown,0x01);
  max_write(max7219_reg_noop,0x01);
  

  
  for (int i =1;i<=8;i++){ //varredura dos 8 digitos
    max_write(i,0);
  }

}



void pulseCS(){    //função responsavel por dar o pulso no CS que por sua vez envia o byte enviado
  digitalWrite(CS,1);
  delay(1);
  digitalWrite(CS,0);
}
