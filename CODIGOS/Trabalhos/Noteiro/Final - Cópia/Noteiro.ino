int corr2 = 1;
boolean estado = 0;
boolean valor = 0;
int efeito_nota = 0;
unsigned long int count = 0;
unsigned long int tempo_ok = 0;


void Noteiro(){
  if (digitalRead(NOT) && !estado){
    valor++;
    estado = 1;
  }
  else if (!digitalRead(NOT)){
    estado = 0;
  }


  if (valor != 0 && count == 0){
    count = millis();
  }
  if (count !=0 and millis()-count>=2000){
    count = 0;
    estado = 0;
    Serial.println(valor);
    valor = 0;
    efeito_nota = 1;
    flag_nota = 1;
  }

  if (efeito_nota){
    if (millis() - tempo_ok >=200){
      corr2 = (corr2 != 10?corr2+1:1);
      cor(corr2);
      executa_cor2();
      tempo_ok = millis();
      efeito_nota = (efeito_nota==25?0:efeito_nota+1); 
      flag_nota = efeito_nota;
    }
  }


}




