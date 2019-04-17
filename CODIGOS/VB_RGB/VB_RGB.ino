int R =  9;
int G = 10;
int B = 11;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
}

void loop() {
  if (Serial.available()>0){
    int comando = Serial.read()-97;

    if (comando <=9)
      analogWrite(R,map(comando,0,9,0,255));

    if (comando >=10 && comando<=19)
      analogWrite(G,map(comando,10,19,0,255)); 

    if (comando >=20)
      analogWrite(B,map(comando,20,29,0,255)); 
  }
}




