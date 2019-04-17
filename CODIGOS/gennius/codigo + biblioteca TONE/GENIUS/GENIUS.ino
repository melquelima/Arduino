
#include <Tone.h>
#include <mills.h>
Tone speakerpin; //Autofalante no pino 12
mills tempo(3000);
int starttune[] = {
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4};
int duration2[] = {
  100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500};
int note[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int duration[] = {
  100, 100, 100, 300, 100, 300};
boolean button[] = {9,10,12,11};    // botões refente as cores azul, verde, amarelo e vermelho
int butnote[]= {
  NOTE_G3,NOTE_A3,NOTE_B3,NOTE_C4};
boolean ledpin[] = {5,6,7,8};  // LEDs   refente as cores azul, verde, amarelo e vermelho
int turn = 0;  
int buttonstate = 0;  
int randomArray[100]; 
int inputArray[100]; 
int pressionados = 0;
int rele = A0;
boolean sair;

void setup() 
{
  Serial.begin(9600);
  speakerpin.begin(A5); // Autofalante no pino 12

  for(int x=0; x<4; x++)  // LED pins are outputs
  {
    pinMode(ledpin[x], OUTPUT);
    pinMode(button[x], INPUT_PULLUP);
  }
  pinMode(rele, OUTPUT);
  digitalWrite(rele,1);
  randomSeed(analogRead(1)); 
  delay(1000);
  ef1();
  delay(1000);
  tempo.on(); //inicia a contagem
}


void loop() 
{   


  for (int i=0; i<10; i++)
  {
    delay(1000);
    Serial.println(""); 
    Serial.print("Turn: ");
    Serial.print(i+1);
    Serial.println("");
    randomArray[i] = random(1, 5);
   for(int x=0; x<=i; x++){
    Serial.print(randomArray[x]);
    but_sound(randomArray[x]-1,1);
    delay(500);
   }
    Serial.println("");
    
    if(i==0){
      int pos = randomArray[i]-1;
      digitalWrite(ledpin[pos],1);
      while(digitalRead(button[pos])){delay(10);}
      but_sound(pos,1);
      delay(200);
      while(!digitalRead(button[pos])){delay(10);}
      
    }


    if (i!=0){
      Serial.print(pressionados);
      Serial.print(" - ");
      Serial.println(i+1);
      tempo.reset(); //inicia a contagem
      while((i+1) != pressionados){
        for(int x=0; x<4; x++){
          if (!digitalRead(button[x])){
            if(randomArray[pressionados] != x+1){
              fail();
              sair = true;
              break;
            }
            but_sound(x,1);
            pressionados++;
            tempo.reset(); //inicia a contagem
            Serial.print(inputArray[pressionados-1]);
            while(!digitalRead(button[x])){delay(10);}
            delay(200);
          }
        }
        if(sair){break;}
           Serial.println(pressionados);
           if(tempo.verifica()){fail();sair = true; break;}
      }
      pressionados = 0;
      Serial.println("");
      if(i>8){ef2();digitalWrite(rele,0);delay(2000);digitalWrite(rele,1); i =0;sair = true; break;}
    }
    if(sair){break;}
  }
  
  sair = false;
pressionados = 0;
 Serial.println("");
 for(int x=0; x<100; x++){
    inputArray[x] = 0;
 }
 
}

//---------------------------------------------------------------------------------------------------------------
void fail() { //rotina de erro

  for (int y=0; y<=2; y++)
  { //piscadas de erro

    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    speakerpin.play(NOTE_G3, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    speakerpin.play(NOTE_C3, 300);
    delay(200);
  }
  delay(500);
  turn = -1; //Reinicia o jogo
}


void ef1(){
  for (int thisNote = 0; thisNote < 13; thisNote ++) {

    speakerpin.play(starttune[thisNote]);

    if (thisNote==0 || thisNote==2 || thisNote==4 || thisNote== 6)
    {
      digitalWrite(ledpin[0], HIGH);
    }
    if (thisNote==1 || thisNote==3 || thisNote==5 || thisNote== 7 || thisNote==9 || thisNote==11)
    {
      digitalWrite(ledpin[1], HIGH);
    }
    if (thisNote==8 || thisNote==12)
    {
      digitalWrite(ledpin[2], HIGH);
    }  
    if (thisNote==10)
    {   
      digitalWrite(ledpin[3], HIGH);
    }
    delay(duration2[thisNote]);

    speakerpin.stop();
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(25);
  }
}

void ef2(){
  digitalWrite(ledpin[0], HIGH);
  digitalWrite(ledpin[1], HIGH);
  digitalWrite(ledpin[2], HIGH);
  digitalWrite(ledpin[3], HIGH);

  for (int thisNote = 0; thisNote < 6; thisNote ++) {

    speakerpin.play(note[thisNote]);

    delay(duration[thisNote]);

    speakerpin.stop();
    delay(25);
  }
  digitalWrite(ledpin[0], LOW);
  digitalWrite(ledpin[1], LOW);
  digitalWrite(ledpin[2], LOW);
  digitalWrite(ledpin[3], LOW);
}

void but_sound(int x,boolean y){
  if (y){
  digitalWrite(ledpin[x], HIGH);
  speakerpin.play(butnote[x], 100);
  delay(400);
  while(!digitalRead(button[x])){delay(10);}
  digitalWrite(ledpin[x], LOW);
  delay(100);
  }else{
  speakerpin.play(butnote[x], 100);
  delay(400);
  }
  
} 


