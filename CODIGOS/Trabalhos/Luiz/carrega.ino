byte p1[8] = {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
byte p2[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
byte p3[8] = {0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C};
byte p4[8] = {0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E};
byte p5[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};

int buz = 7;


void carrega(){
  pinMode(buz,OUTPUT);
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);

}

void bip(){
tone(13,1599,100);delay(100);tone(13,1299,100);delay(100);
tone(13,1499,100);delay(100);tone(13,1399,100);delay(100);
tone(13,1299,100);delay(100);tone(13,1499,100);delay(1000); 
}


void acelera(int tempo) {
float _delay = (10*15.625);

int celula = 0;
lcd.clear();
lcdprint("===ACELERANDO===",0,0);

   for(int j=0;j<16;j++){
   for(int i=1;i<=4;i++){
         lcd.setCursor(celula, 1);
         lcd.write(i);
         if (i == 4){celula++;tone(13,2999,90);}
         if ((i==4)&&(celula==16)){
           lcdprint("=====PRONTO=====",0,0);
             bip();
            celula=0;
         }
         delay(_delay);
    }
}

}


void freia(int tempo){
 lcd.clear();
 lcdprint("====FRENAGEM====",0,0);
 lcdprint("Freios em t = ",1,0);

 while(tempo != 0){
   tone(13,2999,90);
   lcdprint(String(tempo),1,14);
   delay(1000);
   tempo --;
 }
}

 unsigned long int mediana(unsigned long int *valores){
   unsigned long int arrumado[31];
   
 for (int i = 0 ;i<31;i++){
   if (valores[i] <= valores[0]){
     
   }
 }  
   
   
 }

