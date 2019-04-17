
int portas[7] = {13,12,11,10,9,8,7}; // segmento "A" à "G" 

int numeros[10][7]={
{1,1,1,1,1,1,0}, // 0
{0,1,1,0,0,0,0}, // 1
{1,1,0,1,1,0,1}, // 2
{1,1,1,1,0,0,1}, // 3
{0,1,1,0,0,1,1}, // 4
{1,0,1,1,0,1,1}, // 5
{1,0,1,1,1,1,1}, // 6
{1,1,1,0,0,0,0}, // 7
{1,1,1,1,1,1,1}, // 8
{1,1,1,1,0,1,1}  // 9
};

void setup(){

for(int i=0; i<7; i++)
pinMode(portas[i],OUTPUT);  // seta todas as portas como saida

apaga();  // limpa o display

}

void loop(){

  for(int i=0; i<10; i++){ // 0 a 9
        show(i);    // mostra o numero no display
        delay(1000); // delay de 1s
  }
}

void apaga(){  // limpa o display
  
 for(int i=0; i<10; i++)
digitalWrite(portas[i],LOW); // seta todos os segmentos como LOW
}

void show(int numero){
  apaga();  //limpa o display
  for(int i=0; i<7; i++)  // mostra o numero no display
    if(numeros[numero][i]){digitalWrite(portas[i],HIGH);}

}
