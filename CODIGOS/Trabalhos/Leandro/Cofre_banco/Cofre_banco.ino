int dataIn = 9;
int CS = 10;
int clock = 19;

int numero[4] = {0,0,0,0};
int pot0 = A1;
int pot1 = A2;
int pot2 = A3;
int pot3 = A4;
int range[10][2]={{0,40},{62,142},{164,244},{266,346},{328,448},{470,550},{572,652},{674,754},{776,856},{878,958}};
long senha = 0;
int digitado = 0;
int but = 7;
int rele  = 8;
boolean entra = true;

void setup(){
  //EEPROMWritelong(0,9357);
  pinMode(but,INPUT_PULLUP);
  senha = EEPROMReadlong(0);
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(CS,   OUTPUT);
  pinMode(rele,   OUTPUT);
  digitalWrite(CS,0);
  max7219_init();
  display_num(senha);
  pisca();
 
}

void loop() { 
 digitado = pots();
 display_num(digitado);

 if(digitado == senha && entra){
    max7219_ok();
    display_num(digitado);
    digitalWrite(rele,1);
    delay(2000);
    digitalWrite(rele,0);
    entra = false;
 }
  entra = (digitado != senha?true:entra);

  if (!digitalRead(but)){
    EEPROMWritelong(0,digitado);
    pisca();
    while(!digitalRead(but)){}
    delay(2000);
  }
 
}

int pots(){

    int valor1 = analogRead(pot0);
    int valor2 = analogRead(pot1);
    int valor3 = analogRead(pot2);
    int valor4 = analogRead(pot3);
    
    for(int j=0;j<10;j++){
      numero[0] = valor1>=range[j][0] && valor1<=range[j][1]?j:numero[0];
      numero[1] = valor2>=range[j][0] && valor2<=range[j][1]?j:numero[1];
      numero[2] = valor3>=range[j][0] && valor3<=range[j][1]?j:numero[2];
      numero[3] = valor4>=range[j][0] && valor4<=range[j][1]?j:numero[3];
    }

    int m,c,d,u;

    m = numero[0]*1000;
    c = numero[1]*100;
    d = numero[2]*10;
    u = numero[3];

    return m+c+d+u;
}


