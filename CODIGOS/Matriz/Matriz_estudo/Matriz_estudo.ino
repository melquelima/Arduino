typedef struct {
 int largura;
 boolean* matriz;
} letra;
 
boolean __la[5][3] =
{
 {1,1,1},
 {1,0,1},
 {1,1,1},
 {1,0,1},
 {1,0,1}
};
letra __a = { 3, (boolean*)__la };
 
boolean __lb[5][3] =
{
 {1,1,0},
 {1,0,1},
 {1,1,0},
 {1,0,1},
 {1,1,0}
};
letra __b = { 3, (boolean*)__lb };
 
boolean __lc[5][3] =
{
 {0,1,1},
 {1,0,0},
 {1,0,0},
 {1,0,0},
 {0,1,1}
};
letra __c = { 3, (boolean*)__lc };
 
 
 letra* __letras[] = {&__a,&__b,&__c};
 
  boolean mensagem[5][8] = {
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0}
 };
 
 
 void escreve(char letra){
   int num_letra = letra - 65;
   
   for(int i=0; i <=(*(__letras[num_letra])).largura;i++){
     for(int k = 0; k < 5; k++)
     for(int l = 0; l < 8; l++)
       mensagem[k][l] = *((*(__letras[num_letra])).matriz);
     }
   
 }
 

 
 
 void setup(){
   
   Serial.begin(9600);
 }
 
 void loop(){
   escreve('A');


     Serial.println(*((*(__letras[0])).matriz));


    delay(6000);
 }
 
 
