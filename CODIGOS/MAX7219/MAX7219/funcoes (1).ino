
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
