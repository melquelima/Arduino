void setup(){     
Serial.begin(9600);    
}     
void loop(){   
int comando;  
if(Serial.available()>0){
comando = Serial.read();
}
switch(comando){

case 'a':
Serial.println(NivInf());
break; // Retorna se tem água na cisterna

case 'b': // Liga a bomba na cisterna e acompanha o nível da água
encher(); 
break;
}
} 

  
void bomba(int x){  //Responsável por ligar a bomba para encher a caixa   
switch(x){   
case 0: {Serial.println("bomba desligada"); break;}   
case 1:{Serial.println("bomba ligada"); break;}    
}   
 }   

void encher(){ 
boolean nivel_Cisterna; 
boolean nivel_Caixa = false; 
bomba(1); //liga bomba 
do{ 
nivel_Cisterna = NivInf(); //verifica se tem água na cisterna 
nivel_Caixa = nivel_cx();
}while(!nivel_Caixa and nivel_Cisterna); // continua enchendo a caixa enquanto tiver agua na cisterna ou não tiver agua na caixa 
if(!nivel_Cisterna){ // se acabou a agua na cisterna avise ao AC 
Serial.println("Cisterna Vazia"); // comando que diz que acaboua agua na Cisterna 
bomba(0);
} else if(nivel_Caixa){Serial.println("caixa cheia");bomba(0);}
} 

boolean NivInf(){ // Responsavel por verificar se tem agua na cisterna   
//em criação    
//leitura dos sensores da CCisterna  
 int comando;  
if(Serial.available()>0){
comando = Serial.read();
}
switch(comando){
case 'd': //Obs. enviar umas 4 vezes por conta do "do" "dddd"
return false;
break; // Retorna se tem água na cisterna
}
return true;   
}   


boolean nivel_cx(){
 int comando;  
if(Serial.available()>0){
comando = Serial.read();
}
switch(comando){
case 'c':  //Obs. enviar umas 4 vezes por conta do "do" "cccc"
return true;
break; // Retorna se tem água na caixa
}
return false;
}

