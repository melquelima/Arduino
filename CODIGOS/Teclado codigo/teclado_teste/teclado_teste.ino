int portas[8]= {3,4,5,6,8,9,10,11};
//os 4 primeiros numeros para linhas 
//os 4 ultimos numeros para colunas

String senha = "12345";

char letras[4][4] ={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

void setup()
{
for(int i =0;i<4;i++)
  pinMode(portas[i], OUTPUT);
   
for(int i =4;i<8;i++)
  pinMode(portas[i], INPUT);
   
  Serial.begin(9600);
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println("digite a senha com 5 caracteres");
  Serial.println();
}
 
void loop()
{
  
  verifica_tecla();  
}
 
 void verifica_tecla(){
  for (int ti = 0; ti<4; ti++)
    {
    //Alterna o estado dos pinos das linhas
    for(int i =0;i<4;i++)
    digitalWrite(portas[i], 0);
    
    digitalWrite(portas[ti], 1);
    //Verifica se alguma tecla da coluna 1 foi pressionada
    if (digitalRead(portas[4]))
    {
      imprime_linha_coluna(ti+1, 1);
      while(digitalRead(portas[4])){}
    }
 
    //Verifica se alguma tecla da coluna 2 foi pressionada    
    if (digitalRead(portas[5]))
    {
      imprime_linha_coluna(ti+1, 2);
      while(digitalRead(portas[5])){};
    }
     
    //Verifica se alguma tecla da coluna 3 foi pressionada
    if (digitalRead(portas[6]))
    {
      imprime_linha_coluna(ti+1, 3);
      while(digitalRead(portas[6])){}
    }
     
    //Verifica se alguma tecla da coluna 4 foi pressionada
    if (digitalRead(portas[7]))
    {
      imprime_linha_coluna(ti+1, 4);
      while(digitalRead(portas[7])){} 
    }
   }
   delay(10); 
 }
 
 
void imprime_linha_coluna(int L, int C)
{
Serial.println(letras[L-1][C-1]);
}

void compara_senha(){
  
}
