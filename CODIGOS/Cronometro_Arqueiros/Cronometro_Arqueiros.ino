//-----Setar Displays---
#include <AH_74HC595.h>
AH_74HC595 seven_segment1(4, 3, 2); 
AH_74HC595 seven_segment2(7, 6, 5);
AH_74HC595 seven_segment3(10, 9, 8);

//-----Setar Botoes------
int start = A5;
int menu = A0;
//-----Setar Lampadas----
int vermelho = 13;
int amarelo = 12;
int verde = 11;
//----Setar Leds de Botoes---
int led1 = A4;
int led2 = A3;
//----Setar Buzzer -----------
int buzzer = A1;
int buzzerRele = A2;
//----Setar Variavel de menu 120 e 240-----
boolean estado = false;
//----
void setup() {
  //----declarar botoes como entrada---
  pinMode(start,INPUT);
  pinMode(menu,INPUT);
  //----declarar lampadas como saida----
  pinMode(vermelho,OUTPUT);
  pinMode(amarelo,OUTPUT);
  pinMode(verde,OUTPUT);
  //---- declarar leds dos botoes como saida----
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  //---- declarar buzzer como saida -----
  pinMode(buzzer,OUTPUT);
  //---- executa a função limpar-----
  limpa();

}

void loop() {
 
  int start1 = analogRead(start);
  int menu1 = analogRead(menu);
  
  if (menu1 == LOW){
   setaEstado();    
  }
  
   if (start1 == LOW) {
     digitalWrite(led1,HIGH);
    if (estado == false){
      vinte();
      centoVinte();      
    }
    else{
      vinte();
      duzentosQuarenta();      
    }
 }
 digitalWrite(led1,LOW);
}


void vinte(){
  limpa();
  digitalWrite(vermelho,HIGH);
  
  seven_segment3.showNumber(0);
  seven_segment1.showNumber(2);
  seven_segment2.showNumber(0);
  delay(200);
     for (int j=1;j>=0;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(200); 
        }           
     }  
  limpa();
  digitalWrite(vermelho,LOW);
}

void centoVinte(){
  limpa();
  int tempo = 100;
  
  digitalWrite(verde,HIGH);
  
  seven_segment3.showNumber(1);
  seven_segment1.showNumber(2);
  seven_segment2.showNumber(0);
  delay(tempo);
  
  for (int j=1;j>=0;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     }  
     
  seven_segment3.showNumber(0);

  
   for (int j=9;j>=3;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     } 
     digitalWrite(verde,LOW);
     digitalWrite(amarelo,HIGH);
     
     for (int j=2;j>=0;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     } 
    digitalWrite(amarelo,LOW);
    digitalWrite(vermelho,HIGH);
    apito();
    digitalWrite(vermelho,LOW);
    
   limpa();  
}

void duzentosQuarenta(){ //funçao que conta de 240 a 0 
  int tempo = 100;       // variavel tempo declarada como 100mls
  limpa();               //executa a função limpar
  digitalWrite(verde,HIGH); // acende a lampada verde
  
  //------imprime o numero 240 no display-----
  seven_segment3.showNumber(2);
  seven_segment1.showNumber(4);
  seven_segment2.showNumber(0);
  delay(tempo);           // espera 100mls 
  
  // como no primeiro digito esta o numero 2, contamos com apenas
  //os 2 ultimos numeros, ou seja, contamos de 39 a 0 
  // porque o numero quarenta ja se foi imprimido acima
  // assim obteremos o numero 200
  
  // ---contamos de 39 a 0-----
    for (int j=3;j>=0;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     }  
  // agora temos o numero 200 no display e temos que diminuir
 // 1 do primeiro digito com o comando abaixo
 
  seven_segment3.showNumber(1);

  // como tiramos 1 do primeiro digito (centena) obtvemos o numero 100
  // agora temos que contar de 99 a 0 para que se tenha uma contagem
  // regressida 199,198,197.....
  
   for (int j=9;j>=0;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     } 
  // ate aqui contamos de 240 a 100, do mesmo modo temos que 
  // subtrair 1 da centena com o codigo abaixo
     seven_segment3.showNumber(0);
     
 // agora temos que contar de 99 a 30 
     for (int j=9;j>=3;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     } 
     
 // ate agora contamos de 240 a 30 quando chegar em 30 acendemos
 // a lampada amarela sem esquecer de pagar primeiro a lampada
 // verde que ascendemos anteriormente
     digitalWrite(verde,LOW);
     digitalWrite(amarelo,HIGH);

// pos acendermos a lampda amarela continuremos a contagem
// regressiva de 29 a 0 lemprando que o numero 30 ja esta impresso
// no display pelo ultimo for
     for (int j=2;j>=0;j--){
     seven_segment1.showNumber(j);
       for (int j=9;j>=0;j--){
         seven_segment2.showNumber(j);
         delay(tempo); 
        }           
     } 
// chegando aqui contamos de 240 a 0 com a luz verde acesa 
// sendo que quando a contagem chegou em 3o apagamos a luz verde
// e acendemos a amarela, agora na contagem em 0 apagamos a luz
// amarela e acendemos a vermelha esperando um tempo de 2 segundos
    digitalWrite(amarelo,LOW);
    digitalWrite(vermelho,HIGH);
    apito();
    digitalWrite(vermelho,LOW);
   limpa();       // executa a função limpa
}
//===============================================================
void setaEstado(){    // função que muda o valor da variavel "estado"
  estado =! estado;   //o valor atual de estado e diferente dela mesma ou seja se for true sera false e se for false era true
  if (estado == true){  //if que acende o led do botao vermelho
    digitalWrite(led2,HIGH);
  }
  else{
   digitalWrite(led2,LOW); 
    
  }
  delay(400);            // delay estipulado pra dar tempo de apertar o botao sem que o valor altere varias vezes
}



//==================================================================
void limpa() {           // função que limpa os 3 displays
 seven_segment1.clear();
 seven_segment2.clear();
 seven_segment3.clear();
  
}
void apito(){
  
  for (int i=0; i<=3;i++){
    digitalWrite(buzzer,HIGH);
    digitalWrite(buzzerRele,HIGH);
    delay(1000);
    digitalWrite(buzzer,LOW);
    digitalWrite(buzzerRele,LOW);
    delay(1000);
  }
  
}
