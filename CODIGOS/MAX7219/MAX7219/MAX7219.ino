int dataIn = 9;
int CS = 10;
int clock = 19;

byte squar[8]={0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};


void setup(){
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(CS,   OUTPUT);
  digitalWrite(CS,0);
  max7219_init();

//draw(squar);
 
    //    max_write(1,1);
   // delay(100);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
 for(int i = 0;i<=10;i++){
      max_write(7,i);
      max_write(8,i);
      max_write(3,i);
      max_write(4,i);
    delay(500);
  }
}




