int R = 9;    // LED connected to digital pin 9
int G = 10;
int B = 11;

void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 
  
  //----------------LILAZ FADE------------------
    for(int Value = 0 ; Value <= 255; Value +=5) {  
    analogWrite(B, Value);     
    delay(80);}
    for(int Value = 0 ; Value <= 255; Value +=5) {  
    analogWrite(R, Value);     
    delay(80);}
    delay(5000);
  //----------------AMARELO FADE------------------
    for(int Value = 255 ; Value >= 0; Value -=5) {  
    analogWrite(B, Value);     
    delay(80);}
    for(int Value = 0 ; Value <= 255; Value +=5) {  
    analogWrite(G, Value);     
    delay(80);} 
    delay(5000);
  //-----------------ROZA FADE--------------------
    for(int Value = 0 ; Value <= 50; Value +=5) {  
    analogWrite(B, Value);     
    delay(80);}
    for(int Value = 255 ; Value >= 0; Value -=5) {  
    analogWrite(G, Value);     
    delay(80);}
    delay(5000);
    //-----------------AZUL FADE--------------------
    for(int Value = 50 ; Value <= 255; Value +=5) {  
    analogWrite(B, Value);     
    delay(80);}
    for(int Value = 0 ; Value <= 110; Value +=5) {  
    analogWrite(G, Value);     
    delay(80);}
    for(int Value = 255 ; Value >= 0; Value -=5) {  
    analogWrite(R, Value);     
    delay(80);}
    delay(5000); 
  //-------------------TRANSIÇAO DE FASE-------------------
    for(int Value = 110 ; Value >= 0; Value -=5) {  
    analogWrite(G, Value);     
    delay(80);}
    for(int Value = 255 ; Value >= 0; Value -=5) {  
    analogWrite(B, Value);     
    delay(80);}
    delay(3000);
  
//---------------------LILAZ-------------------------------
  for(int Value = 0 ; Value <= 255; Value +=5) { 
    analogWrite(R, Value); 
    analogWrite(B, Value);     
    delay(70);} 
  for(int Value = 255 ; Value >= 0; Value -=5) {
    analogWrite(R, Value); 
    analogWrite(B, Value); 
    delay(70);}
//-------------------------AZUL---------------------------
  for(int Value = 0 ; Value <= 255; Value +=5) { 
    analogWrite(B, Value);            
    delay(70);} 
  for(int Value = 255 ; Value >= 0; Value -=5) {
    analogWrite(B, Value); 
    delay(70);} 
//------------------------VERDE----------------------------
      for(int Value = 0 ; Value <= 255; Value +=5) { 
    analogWrite(G, Value);            
    delay(70);} 
  for(int Value = 255 ; Value >= 0; Value -=5) {
    analogWrite(G, Value); 
    delay(70);} 
//-------------------------VERMELHO---------------------------
      for(int Value = 0 ; Value <= 255; Value +=5) { 
    analogWrite(R, Value);            
    delay(70);} 
  for(int Value = 255 ; Value >= 0; Value -=5) {
    analogWrite(R, Value); 
    delay(70);} 
//--------------------------PISCA CORES------------------------    

analogWrite(R, 255);
analogWrite(G, 255);
delay(500);
analogWrite(R, 0);
analogWrite(B, 255);
delay(500);
analogWrite(B, 0);
analogWrite(G, 255);
delay(500);
analogWrite(G, 0);
analogWrite(R, 255);
delay(500);
analogWrite(B, 255);
delay(500);
analogWrite(B, 50);
delay(500);
analogWrite(R, 255);
analogWrite(G, 255);
delay(500);
analogWrite(R, 0);
analogWrite(B, 255);
delay(500);
analogWrite(B, 0);
analogWrite(G, 255);
delay(500);
analogWrite(G, 0);
analogWrite(R, 255);
delay(500);
analogWrite(B, 255);
delay(500);
analogWrite(B, 50);
delay(500);
analogWrite(R, 0);
analogWrite(G, 0);
analogWrite(B, 0);
delay(200); 





}
