#include "SIM900.h"// inclui a bilioteca do SIM900
#include <SoftwareSerial.h> // //biblioteca responsavel por fazer a comunicação do SIM
#include "sms.h" // blioteca responsavel por tratamento de SMS

SMSGSM sms; // Instacia da biblioteca SMS

boolean started = false;
char smsbuffer[160];
char n[20];


void setup()
{

  Serial.begin(9600); // inicia a counicaçao serial
  if (gsm.begin(9600)) {
    //  Serial.println("\nstatus=READY");
    started = true;
  }

  if (started) {
    //Serial.println("Deleting SMS");
    char error = DeleteAllSMS();
    if (error == 1)Serial.println("All SMS deleted");
    else Serial.println("SMS not deleted");
  }
    //else Serial.println("\nstatus=IDLE");

    //  if (started) {
    // if (sms.SendSMS("5511981281791", "Arduino SMS"))
    //  Serial.println("\nSMS sent OK");

    //}
    //-------------------------- FIM DE CONF DE GSM ------------
    //Serial.println("=====NOVA SENHA======");
    //Serial.println(pega_senha());

  };


  void loop()
  {
    if (started) { // se GSM OK
      if (gsm.readSMS(smsbuffer, 160, n, 20)) { // se oiver SMS disponvel leia e guarde dentro das respectivas variaveis
        // Serial.println(n); // mostre o Numero do remetente
        //Serial.println(smsbuffer); // mostre o sms
      }
      delay(300);// delay de 300 milisegundos
    }
  }

  
  char DeleteAllSMS()
{
     char ret_val = -1;
     char *p_char;
     byte status;

     if (CLS_FREE != gsm.GetCommLineStatus()) return (ret_val);
     gsm.SetCommLineStatus(CLS_ATCMD);
     ret_val = 0; // still not present
 
     gsm.SimpleWriteln(F("AT+CMGDA=\"DEL ALL\""));
 
     switch (gsm.WaitResp(8000, 50, "OK")) {
     case RX_TMOUT_ERR:
          // response was not received in specific time
          ret_val = -2;
          break;

     case RX_FINISHED_STR_RECV:
          // OK was received => SMS deleted
          ret_val = 1;
          break;

     case RX_FINISHED_STR_NOT_RECV:
          // other response: e.g. ERROR => SMS was not deleted
          ret_val = 0;
          break;
     }

     gsm.SetCommLineStatus(CLS_FREE);
     return (ret_val);  
}
