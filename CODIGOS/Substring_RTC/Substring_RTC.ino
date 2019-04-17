void setup() {
Serial.begin(9600);
}

void loop() {
 
  if(Serial.available()){
    String valor = Serial.readString(); 
    String hora = valor.substring(0,2);
    String minuto = valor.substring(2,4);
    String tempo = hora + ':'+ minuto;
    Serial.print("Hora configurada para = ");
    Serial.println(tempo);
  }
  
}
