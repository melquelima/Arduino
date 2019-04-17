void setup() {
Serial.begin(9600);// iniciando a Serial
}

void loop() {
for(int i =1; i<=10; i++){ //laço que conta de 1 à 10s
  if(Serial.read() == '1'){// SE a leitura na Serial  for 1
  Serial.println("");      //quebre a linha
Serial.println("Laco interompido"); // printe na Serial
break;     //interompa o laço
}
Serial.print(i); // Se a leitura da serial nao for = a 1 imprima i
delay(1000);  //de um delay de 1s
if(i == 10){Serial.println("");}// se a contagem chegar em 10 quebre a linha
}  
}
