#include <mills.h>
#include "SIM900.h"// inclui a bilioteca do SIM900
#include <SoftwareSerial.h> // //biblioteca responsavel por fazer a comunicação do SIM
#include "sms.h" // blioteca responsavel por tratamento de SMS
#include <EEPROM.h>

SMSGSM sms; // Instacia da biblioteca SMS

#include <pcfXpand.h> //biblioteca responsavel por fazer a comunicação com o moduo de reles
#include <Wire.h> // responsavel por comunicar o modulo de Reles
#include <Ultrasonic.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     8

mills tempo(3000);
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

pcfXpand pcf(39, OUTPUT); // declara o endereço e o tipo de I/O


boolean started = false;
char smsbuffer[160];
char n[20];
boolean ultra = false;
boolean ativa_buzzer = false;
int buzzer = 11;
boolean entra = false;
String senhaa = pega_senha();
char stt[6];
int panico = 13;

void setup()
{
  tempo.inicio();
  Serial.begin(9600); // inicia a counicaçao serial
  pcf.inicio('A'); // Inicia a comunicação Anodo, C para Catodo
  pcf.digWrite(7, !LOW);
  pcf.digWrite(8, !LOW);
  pinMode(buzzer, OUTPUT);
  pinMode(panico, INPUT_PULLUP);
  digitalWrite(buzzer, !LOW);
  stt[5] = '0';

  if (gsm.begin(9600))
    started = true;


  //Serial.println("=====NOVA SENHA======");
  //Serial.println(pega_senha());

};


void loop()
{


  if (started && tempo.verifica()) { // se GSM OK

    if (gsm.readSMS(smsbuffer, 160, n, 20)) { // se oiver SMS disponvel leia e guarde dentro das respectivas variaveis
      // Serial.println(n); // mostre o Numero do remetente
      //Serial.println(smsbuffer); // mostre o sms
      comando(smsbuffer); // função que trata o sms e sua respectiva função no sistema
    }
    delay(300);// delay de 300 milisegundos
  }

  if (ultra) {
    
    float cmMsec = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);

    ativa_buzzer = (cmMsec > 36 or cmMsec < 33 ? true : false);

    if (ativa_buzzer) {
      digitalWrite(buzzer, !HIGH);
      if (stt[5] == '0') {
        sms.SendSMS(n, "!...:ATF02");
        stt[5] = '1';
      }
    }
  }

int pnc = !digitalRead(panico);
    
    if (pnc) {
      char smms[] = "Socorro! estou sendo Assaltado";

      sms.SendSMS("11989960192", "Socorro! estou sendo Assaltado");
      sms.SendSMS("11980378530", smms);
     // sms.SendSMS("11983820895", smms);
      sms.SendSMS("11981281791", smms);
    //  Serial.println("=========== SOCORRO ENVIADO ================");
    }
  //Serial.println(pnc);
}
void comando (char* com) {

  String senha  = senha + com[5] + com[6] + com[7] + com[8] + com[9] + com[10]; // pega o PIN (Senha) vinda do sms
  String str = str + com[11] + com[12] + com[13] + com[14] + com[15]; // pega o comando do mesmo
  String validado = validado + com[0] + com[1] + com[2] + com[3] + com[4];
  //Serial.print("COMANDO------------------->"); // mostra o comando recebido
  //Serial.println(str); // mostra o comando recebido

  if (validado == "!...:") {
    if (senha == senhaa) { // se a senha estiver correta prossiga
      //Serial.println("=============SENHA OK ==============");
      if (str == "OUT20") { // verifica se o comando é o respectivo
        stt[0] = '0';
        sobe_janela();  // sobe a janela do carro
        sms.SendSMS(n, "!...:OUT20"); //retorna o mesmo como sinal de recebido para o aplicadito
      }
      else if (str == "OUT21") {
        stt[0] = '1';
        dece_janela(); // dece a janela do carro
        sms.SendSMS(n, "!...:OUT21");
      }
      else if (str == "OUT31") {
        stt[1] = '1';
        trava(1); // bloqueia a porta
        sms.SendSMS(n, "!...:OUT31");
      }
      else if (str == "OUT30") {
        stt[1] = '0';
        trava(0); // desbloqueia a porta
        sms.SendSMS(n, "!...:OUT30");
      }
      else if (str == "OUT11") {
        stt[2] = '1';
        pcf.digWrite(6, !HIGH);
        sms.SendSMS(n, "!...:OUT11");
      }
      else if (str == "OUT10") {
        stt[2] = '0';
        pcf.digWrite(6, !LOW);
        sms.SendSMS(n, "!...:OUT10");
      }
      else if (str == "ATF01") {
        stt[3] = '1';
        alarme();
        sms.SendSMS(n, "!...:ATF01");
      }
      else if (str == "ATF00") {
        stt[3] = '0';
        stt[4] = '0';
        ultra = false;
        stt[5] == '0';//aciona so uma vez
        digitalWrite(buzzer, !LOW);
        sms.SendSMS(n, "!...:ATF00");
      }
      else if (str == "GPS00") {
        sms.SendSMS(n, "!...:GPS-23.599819,-46.676373");
      }
      else if (str == "STS00") {
        char * aa[4];
        char c[] = "!...:STS-23.599819;-46.676373;00;0;0;0;0;0";

        c[33] = (stt[0] == '1' ? '1' : '0');
        c[35] = (stt[1] == '1' ? '1' : '0');
        c[37] = (stt[2] == '1' ? '1' : '0');
        c[39] = (stt[3] == '1' ? '1' : '0');
        c[41] = (stt[4] == '1' ? '1' : '0');
        //
        //        if (stt[0] == '1')
        //          c[33] = '1';
        //        else c[33] = '0';
        //
        //        if (stt[1] == '1')
        //          c[35] = '1';
        //        else c[35] = '0';
        //
        //        if (stt[2] == '1')
        //          c[37] = '1';
        //        else c[37] = '0';
        //
        //        if (stt[3] == '1')
        //          c[39] = '1';
        //        else c[39] = '0';

        //char commm[40];
        //stt[0].toCharArray(aa, 1);
        sms.SendSMS(n, c);
      }

      else if (str == "PASSW") {
        String nova_senha = nova_senha + com[16] + com[17] + com[18] + com[19] + com[20] + com[21];
        // Serial.println("*********************");
        //Serial.println(nova_senha);
        salva_senha(nova_senha);
      }
    }
    else { // caso a senha seja incorreta
      sms.SendSMS(n, "!...:PWD0"); // retorne o comando para senha incorreta
    }
  }
}

void sobe_janela() { // função responsavel por subir a janela
  pcf.digWrite(3, !HIGH); // ativa gsm comando janela
  pcf.digWrite(2, !HIGH); // ativa fechameto
  delay(3000);
  pcf.digWrite(3, !LOW); //desativa gsm comando
  pcf.digWrite(2, !LOW); // desativa fechamento


}

void dece_janela() { // função responsavel por descer a janela

  pcf.digWrite(3, !HIGH); // ativa gsm comando janela
  pcf.digWrite(1, !HIGH); // ativa fechameto
  delay(3500);
  pcf.digWrite(3, !LOW); //desativa gsm comando
  pcf.digWrite(1, !LOW); // desativa fechamento

}

void trava(int x) {

  if (x) {
    pcf.digWrite(7, !HIGH);
    delay(1000);
    pcf.digWrite(7, !LOW);
  }
  else {
    pcf.digWrite(8, !HIGH);
    delay(1000);
    pcf.digWrite(8, !LOW);

  }
}

void alarme() {
  trava(1);
  dece_janela();
  ultra = true;
}


String pega_senha() {

  //  char um = ;
  //  char dois = char(EEPROM.read(3));
  //  char tres = char(EEPROM.read(4));
  //  char quatro = char(EEPROM.read(5));
  //  char cinco = char(EEPROM.read(6));
  //  char seis = char(EEPROM.read(7));
  String senha = String(char(EEPROM.read(2))) + String(char(EEPROM.read(3))) + String(char(EEPROM.read(4))) + String(char(EEPROM.read(5))) + String(char(EEPROM.read(6))) + String(char(EEPROM.read(7)));

  return senha;
}

void salva_senha(String password) {
  for (int i = 2; i <= 7; i++)
    EEPROM.write(i, password.substring(i - 2, i - 1).toInt() + 48);

  //  EEPROM.write(2, password.substring(0, 1).toInt() + 48);
  //  EEPROM.write(3, password.substring(1, 2).toInt() + 48);
  //  EEPROM.write(4, password.substring(2, 3).toInt() + 48);
  //  EEPROM.write(5, password.substring(3, 4).toInt() + 48);
  //  EEPROM.write(6, password.substring(4, 5).toInt() + 48);
  //  EEPROM.write(7, password.substring(5, 6).toInt() + 48);

  //Serial.println("=====NOVA SENHA======");
  // Serial.println(pega_senha());
  senhaa = pega_senha();
}


