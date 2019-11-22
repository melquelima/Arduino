void draw(void) {
  u8g.setColorIndex(0);
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_8x13Br); //para o alfabeto completo com caracteres tirar o r do font_8x13Br
  
  if (tela == 0) {
    u8g.drawBitmapP( 0, 0, 16, 64, rook_bitmap);
  }
  if (tela == 1) {
    //u8g.setColorIndex(0);
    //u8g.setColorIndex(1);
    u8g.drawStr( 25, 30, "Thiagogo");
    u8g.drawStr( 37, 50, "Vario v1.1");
  }

  if (tela == 2) {
    //u8g.setColorIndex(0);
    //u8g.setColorIndex(1);

    //temperatura
    _temperatura();
     
    //caixa e m/s vario

    u8g.drawFrame(50, 0, 78, 35); //quadrado vario
    u8g.drawStr(103, 30, "M\057s"); //m/s

    u8g.drawStr(120, 64, "M"); //M altimetro

    //sensibilidade e relogio
     _relogio();

    //altimetro
    _altimetro();

    //vario
    _vario();

    //bateria
    _bateria();

  }

  //-------------------menu-------------
  if (tela == 3) {
    //recupera dados da eeprom

    if (Rend_memo_display == 1) { //indica em qual memori o display esta solicitando
      Rend_memo = 2;
    }
    if (Rend_memo_display == 2) {
      Rend_memo = 22;
    }
    if (Rend_memo_display > 2) {
      Rend_memo = (Rend_memo_display * 20) + 2;
    }

    if (ler == 0) {
      EEPROM.get(Rend_memo, Rhora);
      delay(10);
      Rend_memo = Rend_memo + 1;
      EEPROM.get(Rend_memo, Rminuto);
      delay(10);
      Rend_memo = Rend_memo + 2;
      EEPROM.get(Rend_memo, Rvarioup);
      delay(10);
      Rend_memo = Rend_memo + 4;
      EEPROM.get(Rend_memo, Rvariodown);
      delay(10);
      Rend_memo = Rend_memo + 4;
      EEPROM.get(Rend_memo, RaltitudeMax);
      delay(10);
      Rend_memo = Rend_memo + 4;
      EEPROM.get(Rend_memo, Rganho);
      delay(10);
      ler = 1;
    }

    u8g.drawRFrame(0, 0, 128, 16, 4);
    u8g.setPrintPos(4, 13);
    u8g.print(Nmeno_display);// numero do voo
    u8g.drawStr(20, 13, "Voo");

    //Mostra memoria dos voos


    String Rtimex = ""; //organiza a hr do voo
    if (Rhora < 10) {
      Rtimex += "0";
    }
    Rtimex += Rhora;
    Rtimex += ":";
    if (Rminuto < 10) {
      Rtimex += "0";
    }
    Rtimex += Rminuto;

    u8g.drawStr(45, 13, "Dur.");
    u8g.setPrintPos(80, 13);
    u8g.print(Rtimex); //memoria eeprom aqui
    //u8g.drawStr(22, 31, ":");
    u8g.drawTriangle(10, 22, 20, 31, 0, 31);
    u8g.setPrintPos(26, 31);
    u8g.print(Rvarioup, 1); //memoria eeprom aqui
    //u8g.drawStr(82, 31, ":");
    u8g.drawTriangle(70, 30, 79, 22, 62, 22);
    u8g.setPrintPos(82, 31);
    u8g.print(Rvariodown, 1); //memoria eeprom aqui
    u8g.drawStr(0, 47, "Alt.Max:");
    u8g.setPrintPos(68, 47);
    u8g.print(RaltitudeMax, 1); //memoria eeprom aqui
    u8g.drawStr(0, 64, "Ganho:"); //fazer conta da maxima menos decolagem
    u8g.setPrintPos(50, 64);
    u8g.print(Rganho, 1); //memoria eeprom aqui
  }

  if (tela == 4) {
    u8g.drawStr( 25, 30, "Deletando");
    u8g.drawStr( 37, 50, "Memoria");
    delay(500);
    menu = 5;
  }

  if (tela == 5) {
    u8g.drawStr( 25, 35, "OK");
    delay(500);
    menu = 2;
  }
}

void _temperatura(){
    u8g.setPrintPos(0, 14);
    u8g.print(Temperature, 1);
    u8g.drawStr( 35, 14, "C"); //acentos http://www.ascii-code.com/
}

void _vario(){
   unsigned char posVar = 0;
    posVar = (vario < 0 ? 52 : 61);
    
    if (vario < -0.1) {
      u8g.drawTriangle(113, 15, 122, 7, 105, 7);
    }
 
    if (vario > 0.1) {
      u8g.drawTriangle(114, 6, 124, 15, 104, 15);
    }
    
    u8g.setPrintPos(posVar, 27);
    u8g.print(vario, 1);
}

void  _bateria(){
    int vcc = (vRef.readVcc()-3500)/100;

    u8g.drawFrame(4, 42, 4, 2);
    u8g.drawFrame(2, 44, 8, 18);

        
    if (vcc > 1) {
      u8g.drawStr( 1, 60, ".");
    }
    if (vcc > 2) {
      u8g.drawStr( 1, 55, ".");
    }
    if (vcc > 3) {
      u8g.drawStr( 1, 50, ".");
    }
}

void _altimetro(){
    unsigned char posAlt = 0;
    posAlt = (Altitude >= 1000? 28 : 48);
    u8g.setFont(u8g_font_fub20n); //se for so numeros usar o n no fim u8g.setFont(u8g_font_fub20n);
    u8g.setPrintPos(posAlt, 64);
    u8g.print(Altitude, 1);
}

void _relogio(){
    if (relogio == 1) {
      u8g.drawStr(0, 30, "v");
      u8g.setPrintPos(10, 30);
      u8g.print(mux);
    }
    else {
      String timex = "";
      String H = (hora < 10?"0": "") + hora;
      String M = (minuto < 10?"0": "") + minuto;
      String P = (segundo % 2 == 0? ":" : " ");
      timex = H + P + M;

      u8g.setPrintPos(0, 34);
      u8g.print(timex);
    }
}

