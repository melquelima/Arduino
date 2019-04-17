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

void pisca(){
  for(int i =0;i<5;i++){
  max_write(max7219_reg_shutdown,0x00);
  delay(500);
  max_write(max7219_reg_shutdown,0x01);
  delay(500);
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

void max7219_ok(){
  max_write(max7219_reg_decodeMode,0x00);

  int anim[12][2]={{4,64},{3,64},{7,64},{8,64},{8,96},{8,112},{8,120},{7,72},{3,72},{4,72},{4,76},{4,78}};
  int anim2[12][2]={{4,64},{3,64},{7,64},{8,64},{8,32},{8,16},{8,8},{7,8},{3,8},{4,8},{4,4},{4,2}};
  int anim3[12][2]={{4,14},{3,8},{7,8},{8,56},{8,24},{8,8},{8,0},{7,0},{3,0},{4,6},{4,2},{4,0}};

  for (int j =0;j<10;j++){
  for (int i =0;i<12;i++){ //varredura dos 8 digitos
    max_write(anim[i][0],anim[i][1]);
    //max_write((anim[i-1][0] == anim[i][0]?0:anim[i-1][0]),0);
    delay(15);
  }
  for (int i =0;i<12;i++){ //varredura dos 8 digitos
    max_write(anim3[i][0],anim3[i][1]);
    //max_write((anim3[i-1][0] == anim3[i][0]?0:anim3[i-1][0]),0);
    delay(15);
  }

  }
max_write(max7219_reg_shutdown,0x00);

   for (int i =0;i<12;i++){ //varredura dos 8 digitos
    max_write(anim[i][0],anim[i][1]);
  }
pisca();
max_write(max7219_reg_decodeMode,0xff);
}

void display_num(int X){
  int M,C,D,U;
  M = X/1000;
  C = (X-(M*1000))/100;
  D = (X-(M*1000)-(C*100))/10;
  U = (X-(M*1000)-(C*100)-(D*10));
  max_write(4,M);
  max_write(3,C);
  max_write(7,D);
  max_write(8,U);
}


void pulseCS(){    //função responsavel por dar o pulso no CS que por sua vez envia o byte enviado
  digitalWrite(CS,1);
  delay(1);
  digitalWrite(CS,0);
}
