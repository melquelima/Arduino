int a,b,c;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
if(Serial.available()>0){
 
 if(Serial.read() == '$') // Inicio do dado
 {
   do{ // leitura do 1 dado
    a = Serial.read();   
   }while(a == '$' or a == -1);
 
  do{ // leitura do 2 dado
    b = Serial.read();   
   }while(b == -1 or b == ',');
 
 do{ // leitura do 3 dado
    c = Serial.read();   
   }while(c == -1 or c == ',');
 
Serial.print(a);
Serial.print(" - ");
Serial.print(b);
Serial.print(" - ");
Serial.println(c);

 } 
 
}

}

