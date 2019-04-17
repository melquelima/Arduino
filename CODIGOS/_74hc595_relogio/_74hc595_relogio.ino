int seg[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CLK = 10;
int LTCH = 9;
int DT = 11;
int bot = 12;
int conf_seg = 0;

void setup(){
  pinMode(CLK,OUTPUT);
  pinMode(LTCH,OUTPUT);
  pinMode(DT,OUTPUT);
  pinMode(bot,INPUT_PULLUP);
  conf_seg = 4;
}

void loop(){
   for(int k = 0; k<24;k++){
      segundos(k);
      delay(500);
   }
}







void segundos(int x){
 
 if(conf_seg == 2){
    seg[x] = 1;
      seg[x-1] = 0;
    if(x == 0){seg[23] = 0;}
 }
 if(conf_seg == 3){
 seg[x] = !seg[x]; 
 }
 if(conf_seg == 4){
    seg[x] = 1;
      if(x==0){seg[23] = 1;seg[22] = 0;seg[1] = 1;}
      if(x==1){seg[23] = 0;seg[0] = 1;seg[2] = 1;}
      if(x==2){seg[3] = 1;seg[1] = 1;seg[0] = 0;}
      if(x==23){seg[0] = 1;seg[21] = 0;}
    if((x > 2)&& (x<23)){seg[x-1] = 1;seg[x+1] = 1;seg[x-2] = 0;}
}

 int shift = 0;
   for(int i = 0; i<2;i++){
    digitalWrite(LTCH,LOW);
      for (int j = 0+shift; j<=7+shift;j++){
        digitalWrite(CLK,LOW);
        digitalWrite(DT,seg[j]);
        digitalWrite(CLK,HIGH);
      }  
  digitalWrite(LTCH,HIGH);
  shift = shift+8;
  }

  
  
}


