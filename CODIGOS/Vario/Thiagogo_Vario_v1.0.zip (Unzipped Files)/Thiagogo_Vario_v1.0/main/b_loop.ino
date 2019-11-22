
void loop(void)
{

  //oled display
  time = millis() / 300;
  u8g.firstPage();
  // Tempo de calibragem
  //tela = (time <= 15?0:(time >10 && time <= 25?1:menu))

  if (time <= 15)
  {
    tela = 0;
  }
  else if (time > 10 && time <= 25) {
    tela = 1;
  }
  else
  {
    tela = menu;

    //--------------salvar dados-----------

    Mvarioup = (vario > Mvarioup?vario:Mvarioup); //grava na variavel a maior acendente

    MaltitudeMax = (Altitude > MaltitudeMax ? Altitude : MaltitudeMax);

    //grava na variavel a maior Altitude e ganho comparando com a decolagem

    MaltitudeDec = Altitude;

    if (millis() - temp_alt < 0)
    {
      temp_alt = millis();
    }
    else {
      temp_verif_alt = int((millis() - temp_alt) / 1000); // contador de segundos
    }
    if (temp_verif_alt > 20 && decolagem == 0) { // verifica de 20 em 20 segundos
      temp_verif_alt = 0;
      MaltitudeDec = Altitude;

      if ((Altitude - ult_altitude < -5.0 || Altitude - ult_altitude > 5.0) && menu == 2) {
        decolagem = 1;
      }
    }
    ult_altitude = MaltitudeDec;

    Mganho = MaltitudeMax - MaltitudeDec;



    //se depois de 5 segundos a variação de altura nao for maior que 2 metros salva voo na memoria

    if ((Mpouso - Altitude < 2 || Mpouso - Altitude > -2) && menu == 2 && endfly == 0 && decolagem == 1) {
      gravatempo = millis();
      endfly = 1;
    }

    Mpouso = Altitude;
    if (Mpouso - Altitude < 2 && Mpouso - Altitude > -2 && menu == 2 && endfly == 1) {
      if (millis() - gravatempo > 5000) {

        //salva a porra toda na eeprom!!!
        EEPROM.write(1, num_memo); //grava o numero da memoria da ultima gravação de voo, para sobrescrever a mais antiga.
        delay(10);

        if (num_memo == 1) { //local para primeira memoria local 2 do eeprom
          end_memo = 2;
        }
        if (num_memo == 2) {
          end_memo = 22;

        }
        if (num_memo > 2) {
          end_memo = (num_memo * 20) + 2;
        }

        EEPROM.put(end_memo, hora);
        delay(10);
        end_memo = end_memo + 1;
        EEPROM.put(end_memo, minuto);
        delay(10);
        end_memo = end_memo + 2;

        EEPROM.put(end_memo, Mvarioup);
        delay(10);
        end_memo = end_memo + 4;
        EEPROM.put(end_memo, Mvariodown);
        delay(10);
        end_memo = end_memo + 4;
        EEPROM.put(end_memo, MaltitudeMax);
        delay(10);
        end_memo = end_memo + 4;
        EEPROM.put(end_memo, Mganho);
        delay(10);


        endfly = 0;

        /*eeprom
           1 memoria principal contagem de voos
           2 hora
           3 minuto
           4 vazio
           5-8 ascendente max
           9-12 descendente max
           13-16 altitude max
           17-20 - ganho
        */

      }
    }
  }



  int currentState = (digitalRead (4));
  if (currentState != buttonState) {
    duration = millis();
    resettime = millis();
  }
  if (currentState == LOW) {
    if ((millis() - duration > 50) && (millis() - duration < 2000) && menu == 2 && estadobotao == 0) {
      countPressVal++;
      tone(tone_out1, 1800, 40);
      delay(80);
      if (countPressVal > 2) {
        countPressVal = 0;
      }

      //mostra relogio e variaçaõ
      lastMillis = millis();
      relogio = 1;
      estadobotao = 1;
    }

    if (millis() - duration > 3000 && menu == 2 && estadobotao == 1) {
      //voos gravados
      ler = 0;
      menu = 3;
      duration = millis();
    }
    if (millis() - duration > 3000 && menu == 3 && estadobotao == 1) {
      //tela vario
      menu = 2;
      Nmeno_display = 1;
      Rend_memo_display = EEPROM.read(1);
      duration = millis();
    }

    //menu configurações
    if (millis() - resettime > 9000 && (menu == 2 || menu == 3) && estadobotao == 1) {

      menu = 4;

      // grave 0 em todos os 512 bytes da EEPROM
      for (int i = 0; i < 512; i++)
        EEPROM.write(i, 0);
      Nmeno_display = 1;
      Rend_memo_display = EEPROM.read(1);
      resettime = millis();
    }

    if ((millis() - duration > 5) && (millis() - duration < 2000) && menu == 3 && estadobotao == 0) {
      ler = 0;
      Nmeno_display++; // mostra so o numero do voo
      Rend_memo_display--; //puxa a pemoria de voo da mais rescente pra mais antiga
      if (Rend_memo_display < 1) {
        Rend_memo_display = 20;
      }
      if (Nmeno_display > 20) {
        Nmeno_display = 1;
      }
      estadobotao = 1;
    }


  }
  if (currentState == HIGH) {
    estadobotao = 0;
  }
  buttonState = currentState;




  // == MENU SENSIBILIDADE PARA LEVANTAR ==
  if ((countPressVal) == 0) {
    mux = 0.3; // 1 sinal
  }
  if ((countPressVal) == 1) {
    mux = 0.5; // 2 sinal
  }
  if ((countPressVal) == 2) {
    mux = 0.8; // 3 sinal
  }
  vario_up = mux;

  //mostra relogio e variaçaõ
  if (lastMillis > 0 && (millis() - lastMillis > 3000))
  {
    relogio = 0;
    lastMillis = 0;
  }

  float tempo = millis();
  float N1 = 0;
  float N2 = 0;
  float N3 = 0;
  float D1 = 0;
  float D2 = 0;
  Altitude = (sensor_bmp.readAltitude(1013.25));
  Temperature = (sensor_bmp.readTemperature());



  for (int cc = 1; cc <= maxsamples; cc++) {                           // averager
    alt[(cc - 1)] = alt[cc];
    tim[(cc - 1)] = tim[cc];
  };
  alt[maxsamples] = Altitude;
  tim[maxsamples] = tempo;
  float stime = tim[maxsamples - samples];
  for (int cc = (maxsamples - samples); cc < maxsamples; cc++) {
    N1 += (tim[cc] - stime) * alt[cc];
    N2 += (tim[cc] - stime);
    N3 += (alt[cc]);
    D1 += (tim[cc] - stime) * (tim[cc] - stime);
    D2 += (tim[cc] - stime);
  };

  vario = 1000 * ((samples * N1) - N2 * N3) / (samples * D1 - D2 * D2); // Cálculo de som

  if ((tempo - beep) > Beep_period)
  {
    beep = tempo;
    if (vario > vario_up && vario < 15 )
    {
      Beep_period = 350 - (vario * 10);
      tone(tone_out1, (1000 + (100 * vario)), 300 - (vario * 5)); // Som em ascensão
      tone(tone_out2, (1003 + (100 * vario)), 300 - (vario * 5));
      thermalling = true;
    }
    else if ((vario < 0 ) && (thermalling == true))
    {
      thermalling = false;
      // tone_out2.play(200, 800); Predpotok // Som (é opcional)

    }
    else if (vario < vario_down && vario > vario_emergence) {        // Som a afundar
      Beep_period = 200;
      tone(tone_out1, (300 - (vario)), 340);
      tone(tone_out2, (303 - (vario)), 340);
      thermalling = false;
    }
    else if (vario < vario_emergence) {        // Som emergencia
      Beep_period = 200;
      tone(tone_out1, 2000, 250);
      tone(tone_out2, 2003, 250);
      delay(200);
      tone(tone_out1, 1000, 250);
      tone(tone_out2, 1003, 250);
      thermalling = false;
    }
  }

  //relogio
  if (decolagem == 1) { //inicia o cronometro quando detectada a decolagem
    if (millis() - UtlTime < 0)
    {
      UtlTime = millis();
    }
    else {
      segundo = int((millis() - UtlTime) / 1000);
    }
    if (segundo > 59)
    {
      segundo = 0;
      minuto++;
      UtlTime = millis();
      if (minuto > 59)
      {
        hora++;
        minuto = 0;
      }
    }
  }
  else {
    segundo = 00;
    minuto = 00;
    hora = 00;
  }

  //-----------mostrar telas-----------
  do {
    draw();
  } while ( u8g.nextPage() );
  //fim oled display
}
