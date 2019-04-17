int  botA = 8;
int botB = 7;
int botC = 6;

int led_A = 13;
int led_B = 12;
int led_C = 10;
int led_X = 9;

int buz = 5;
int rele = 4;
int botao = 3;

void setup() {                

  pinMode(botA, INPUT);
  pinMode(botB, INPUT); 
  pinMode(botC, INPUT);
  pinMode(led_A, OUTPUT); 
  pinMode(led_B, OUTPUT); 
  pinMode(led_C, OUTPUT);
  pinMode(led_X, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(botao, INPUT);  
Serial.begin(9600);
}


void loop() {

  
  
  int A = digitalRead(botA);
  int B = digitalRead(botB);
  int C = digitalRead(botC);
   Serial.print(A);
    Serial.print(B);
     Serial.println(C);
     
     digitalWrite(led_A,A);
     digitalWrite(led_B,B);
     digitalWrite(led_C,C);
     
     
     
  if(A && !B && !C)
    while(!C && A){
     Serial.println("bomba ligada"); 
       digitalWrite(rele,HIGH);
       digitalWrite(led_X,1);
     C = digitalRead(botC);
     A = digitalRead(botA);
     B = digitalRead(botB);
     digitalWrite(led_A,A);
     digitalWrite(led_C,C);
     digitalWrite(led_B,B);
        digitalWrite(buz,1);
    }
   
  if((A && !B && C) or (!A && !B && C))
  {
   Serial.println("Erro");  
   digitalWrite(rele,LOW);
   digitalWrite(led_X,0);
   digitalWrite(buz,0);
  }
   
    if((B && C) or (!A && !B && !C))
    {
       Serial.println("Desliga");
      digitalWrite(rele,LOW);
      digitalWrite(led_X,0);
      digitalWrite(buz,1);
}

    if(!A && B && !C)
    {
       Serial.println("Desliga");
      digitalWrite(rele,LOW);
      digitalWrite(led_X,0);
      digitalWrite(buz,1);
}

    if(digitalRead(botao))
    {
          while(!C && A){
     Serial.println("Enchendo"); 
       digitalWrite(rele,HIGH);
       digitalWrite(led_X,1);
     C = digitalRead(botC);
     A = digitalRead(botA);
     B = digitalRead(botB);
     digitalWrite(led_A,A);
     digitalWrite(led_C,C);
     digitalWrite(led_B,B);
        digitalWrite(buz,1);
    }
    }

}


