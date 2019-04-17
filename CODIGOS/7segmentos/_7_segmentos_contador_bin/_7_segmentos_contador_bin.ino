int portas[7] = {13,12,11,10,9,8,7};

void setup() {
for(int i=0; i<7; i++)
pinMode(portas[i],OUTPUT);
 

  
}

void loop() {
   
   for(int i=0; i<10;i++){
 show(i);
  delay(1000);
   }
}

void show(int numero){
  
  int bin = converte(numero);


for (int x = 0; x <7; x++) {
         
      if (bin & (1 << x)) {
         digitalWrite(portas[x],HIGH);
      } else {
       digitalWrite(portas[x],LOW);
      }
}
}


int converte(int numm){
  
 
switch(numm){
    case 0:
   return 63;
  break;
    case 1:
  return 6;
  break;
    case 2:
   return 91;
  break;
    case 3:
  return 79;
  break;
    case 4:
    return 102;
  break;
    case 5:
    return 109;
  break;
    case 6:
    return 125;
  break;
    case 7:
    return 7;
  break;
    case 8:
    return 127;
  break;
    case 9:
    return 111;
  break;
  
} 
  
}
