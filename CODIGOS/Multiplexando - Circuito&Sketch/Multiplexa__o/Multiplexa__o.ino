int A = 8; // Setando os pinos que serao ultilizados
int B = 9;
int C = 10;

void setup() {
apagaTudo(); //Apagamos todos os LEDS
}

void loop() {
  for(int i = 1; i<=6;i++){ //loop de 1 a 6  que acende cada LED
  led(i);     //manda acender o LED determinado
  delay(1);   // entervalo de tempo entre cada led
  apagaTudo(); //apaga todos os LEDS e passa para o proximo no FOR
  }
  
}

void led(int x){ // o parametro x e o determinado led que voce deseja acender
                 // LED1 à LED6
  
  switch(x){  //SE x for
  case 1:     // iqual a 1
  setar(A,B); //Setar A e B como saida 
  digitalWrite(A,LOW); //padrao para acender o LED1
  digitalWrite(B,HIGH); // ||          ||
  break;
  
  case 2:
  setar(A,B);
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  break;
  
    case 3:
  setar(B,C);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  break;
  
    case 4:
  setar(B,C);
  digitalWrite(B,HIGH);
  digitalWrite(C,LOW);
  break;
  
    case 5:
  setar(A,C);
  digitalWrite(A,LOW);
  digitalWrite(C,HIGH);
  break;
  
    case 6:
  setar(A,C);
  digitalWrite(A,HIGH);
  digitalWrite(C,LOW);
  break;
  }
}

void apagaTudo(){  //com esse comando as portas ABC sao setadas
 pinMode(A,INPUT); //como INPUT porque elas tem que ser NEUTRAS 
 pinMode(B,INPUT); //ou seja nao podem ser nem HIGH e nem LOW
 pinMode(C,INPUT); 
}

void setar (int w, int z){ //os parametros W e Z sao as portas que
 pinMode(w,OUTPUT);        //seram ultilizadas pra acender determinado LED
 pinMode(z,OUTPUT);   //setamos elas como saida, Note que apenas 2 permanecem como OUTPUT 
                      //a outra continua NEUTRA como INPUT setada pela função apagaTudo()
  
}
