 String valor;
void setup() {
Serial.begin(9600);
}

void loop() {

  if(Serial.available()){
    valor = Serial.readString(); 
    int comando = valor.substring(0,1).toInt();

    switch(comando){
    case 1: Config_Luzes(); break;
    case 2: Luzes(); break;
    case 3: Config_Alim(); break;
  }
  }
}


void Config_Luzes(){
  
  String hora = valor.substring(1,3);
  String minuto = valor.substring(3,5);
  
  String tempo = hora + ':' + minuto;
    Serial.print("Luz configurada para = ");
    Serial.println(tempo);
}

void Luzes(){
  
  int estado = valor.substring(1,2).toInt();
 
   if(estado){
     Serial.println("Luz Acesa");
   }else{Serial.println("Luz Apagada");}
}

void Config_Alim(){
  
  int estado = valor.substring(1,2).toInt();
 
   if(estado == 1){
    String hora = valor.substring(2,4);
    String minuto = valor.substring(4,6);
    String tempo = hora + ':'+ minuto;
    Serial.print("Alimentação configurada para = ");
    Serial.println(tempo);
   }
   else if(estado == 2){
       String hora = valor.substring(2,4);
    String minuto = valor.substring(4,6);
     String hora2 = valor.substring(6,8);
    String minuto2 = valor.substring(8,10);
    String tempo = hora + ':'+ minuto;
       String tempo2 = hora2 + ':'+ minuto2;
    Serial.print("Alimentação configurada para = ");
    Serial.print(tempo);
     Serial.print(" e ");
    Serial.println(tempo2);
   }
}

