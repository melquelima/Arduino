

void setup()
{
  Wire.begin();                   // Inicializa i2c
  pinMode(4, INPUT_PULLUP);
  pinMode(tone_out1, OUTPUT);  // Dinâmica pin8 de saída -
  pinMode(tone_out2, OUTPUT);  // Speaker pin9 saída +
  sensor_bmp.begin(); // Sensibilidade do sensor de pressão
  vRef.begin(); //inicia leitura da voltagem da bateria
  //ler memoria a gravar
  num_memo = EEPROM.read(1); //ultima gravação antes de ser desligado
  delay(10);
  num_memo ++;
  num_memo = (num_memo > 20 || num_memo < 1 ? 1 : num_memo);
  Rend_memo_display = EEPROM.read(1);
  play_welcome_beep();
}
