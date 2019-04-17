void config_peso(){
  lcd.clear();
//  lcdprint("INSIRA A MOTO",0,0);
//  lcdprint("PARA PESAGEM",1,0);
//  while(digitalRead(sensor_moto)){
//  }
//  lcd.clear();
  lcdprint("===PESANDO===",0,0);
  delay(3000);

  peso_moto = _getpeso(1);

  Serial.print("PESO DA MOTO == > ");
  Serial.println(peso_moto);
}


void leitura(int tempo){
  float _delay = (10*15.625);

  int celula = 0;
  lcd.clear();
  lcdprint("===FREANDO===",0,0);

  for(int j=0;j<16;j++){
    for(int i=1;i<=4;i++){
      lcd.setCursor(celula, 1);
      lcd.write(i);
      if (i == 4){
        celula++;
        tone(13,2999,90);
        F_frenagem = _getpeso(0);
      }
      if ((i==4)&&(celula==16)){
        lcdprint("=====PRONTO=====",0,0);
        bip();
        celula=0;
        Serial.print("PESO MOTOR ==> ");
        Serial.println(F_frenagem);
      }
      delay(_delay);
    }
  }

 /*
 for (int i = 0 ;i<31;i++){
   F_frenagem[i] = _getpeso(0);
 }
 
 mediana(F_frenagem);
*/

}

