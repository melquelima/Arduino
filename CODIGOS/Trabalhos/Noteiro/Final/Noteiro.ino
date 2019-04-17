int corr2 = 1;
boolean estado = 0;
boolean valor = 0;
int efeito_nota = 0;
unsigned long int count = 0;
unsigned long int tempo_ok = 0;
unsigned long int tempo_relay = 0;
boolean baixo = 1;

void loop2() {
  if (digitalRead(NOT) && !estado) {
    valor++;
    estado = 1;
    count = millis();
  }
  else if (!digitalRead(NOT)) {
    estado = 0;
  }


  //if (valor != 0 && count == 0) {
  //  count = millis();
  //}

  if (count != 0 and millis() - count >= 1000) {

    count = 0;
    estado = 0;
    if (valor <= 5) {
      digitalWrite(R1, 1);
    } 
    if (valor > 5 && valor <= 10) {
      digitalWrite(R2, 1);
    } 
    if (valor > 10 && valor <= 20) {
      digitalWrite(R3, 1);
    }

    Serial.println(valor);
    valor = 0;
    efeito_nota = 1;
    flag_nota = 1;
  }

  if (efeito_nota) {
    if (millis() - tempo_ok >= 200) {
      corr2 = (corr2 != 10 ? corr2 + 1 : 1);
      cor(corr2);
      executa_cor2();
      tempo_ok = millis();
      efeito_nota = (efeito_nota == 25 ? 0 : efeito_nota + 1);
      flag_nota = efeito_nota;
    }
    digitalWrite(ENABLE, 1);
  }




  if ((digitalRead(R1) || digitalRead(R2) || digitalRead(R3)) && tempo_relay == 0) {
    tempo_relay = millis();
  }

  if ((millis() - tempo_relay >= 1000) && tempo_relay != 0) {
    digitalWrite(R1, 0);
    digitalWrite(R2, 0);
    digitalWrite(R3, 0);
    tempo_relay = 0;
  }

}








