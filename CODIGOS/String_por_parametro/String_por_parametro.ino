void setup() {
  Serial.begin(9600);
  //quebra("arduino:melque:joao:Robson:12364");
}

void loop() {
if (Serial.available()){
  String comando = Serial.readString();
  char* valor; 
  int tam = comando.length();
  comando.toCharArray(valor,tam);
  Serial.println(tam);
  quebra(valor);
}

}


void quebra(char* texto) {
  int pos = 0;
  int tamanho = strlen(texto);
  String valor[10];
  for (int i = 0; i < tamanho; i++) {
    if (texto[i] != ':') {
      valor[pos] = valor[pos] + texto[i];
    } else {
      pos++;
    }
  }
  
  Serial.print("Valor1: ");
  Serial.println(valor[0]);
  Serial.print("Valor2: ");
  Serial.println(valor[1]);
  Serial.print("Valor3: ");
  Serial.println(valor[2]);
  Serial.print("Valor4: ");
  Serial.println(valor[3]);
  Serial.print("Valor5: ");
  Serial.println(valor[4]);
}



