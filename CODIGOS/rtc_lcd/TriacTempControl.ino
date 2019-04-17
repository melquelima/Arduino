/*
Programa: TriacTempControl
Controle PID usando triac e detetor de zero.
*/
#include <SPI.h>
#include "Nanoshield_Thermocouple.h"
#include "TimerOne.h"

// Termopar
Nanoshield_Thermocouple thermocouple;

int triac = 3; // Triac: pino D3
int zc = 2;    // Detetor de zero: pino D2

// Tempo entre a detecção de zero e o acionamento do triac
//   (de 0 a 7331 microssegundos)
int time = 7331;

// Set point
float r1 = 50;                 // Set point antes de iniciar a rampa
float r2 = 90;                 // Set point do final da rampa

// Ganhos do PID
float kp = 18.0;               // Ganho proporcional
float ki = 0.02;               // Ganho integral
float kd = 0.25;               // Ganho derivativo

// Variáveis do PID
float r;                       // Set point
float y;                       // Variável observada
float u;                       // Saída do PId (0 a 255)
float e;                       // Erro
float eDot;                    // Variação do erro
float eSum = 0;                // Soma do erro
float ePrev;                   // Erro na última iteração

// Tempo inicial antes de executar a rampa, em ms (para estabilizar o sistema)
unsigned long stepDelay = 60000;

// Controle da rampa
float duration = 0;            // Duração da rampa (ms)

void setup()
{
  Serial.begin(115200);

  // Inicializa os pinos como entrada ou saída
  pinMode(triac, OUTPUT);
  pinMode(zc, INPUT);

  // Inicializa o termopar  
  thermocouple.begin();

  // Associa a borda de subida do detetor de zero com
  //   a função dimmer1(), que desliga o triac e espera
  //   o momento necessário de ativá-lo
  attachInterrupt(0, dimmer1, RISING);
  
  // Inicializa o timer 1
  Timer1.initialize(1000000);

  // Inicializa o PID
  thermocouple.read();
  ePrev = r - thermocouple.getExternal();
  delay(500);
}

void loop()
{
  thermocouple.read();
  
  // Calcula o set point (r)
  if (millis() < stepDelay) {
    // Não começou a rampa ainda
    r = r1;
  } else {
    r = r2;
    // Começou a rampa, calcula o set point com base no tempo
    if (millis() < (stepDelay + duration)) {
      r = (millis() - stepDelay)*(r2 - r1)/duration + r1;
    }
  }
  
  // Lê a temperatura
  y = thermocouple.getExternal();

  // Executa o PID
  e = r - y;
  eSum = eSum + e;
  eDot = e - ePrev;
  u = kp*e + ki*eSum + kd*eDot;
  ePrev = e;
  if (u < 0) u = 0;
  if (u >= 255) u = 255;
  
  // Converte a saída do PID (mínimo = 0, máximo = 255) para um tempo de acionamendo
  //   do triac (intensidade mínima = 7331ms, intensidade máxima = 0ms).
  int t = 7331 * (1 - u/255);
  
  // Atualiza a variável "time", desabilitando as interrupções
  //   para que não haja conflito no acesso.
  noInterrupts();
  time = t;
  interrupts();
  
  // Envia os dados para monisoramento via USB
  Serial.print("{ \"temp\": ");
  if (thermocouple.isShortedToVcc() || thermocouple.isShortedToGnd() || thermocouple.isOpen()) {
    Serial.print("null");
  } else {
    Serial.print(y);
  }
  Serial.print(", \"ref\": ");
  Serial.print(r);
  Serial.print(", \"output\": ");
  //Serial.print(ki*eSum);
  Serial.print(u * 100 / 255);
  Serial.print(" }\n\n");
  
  delay(500);
}

void dimmer1()
{
  // Desativa o triac
  digitalWrite(triac, LOW);

  // Espera até o momento correto (variável "time") e aciona o triac
  Timer1.start();
  Timer1.attachInterrupt(dimmer2, time + 500);
}

void dimmer2()
{
  // Ignora interrupção inicial
  Timer1.attachInterrupt(dimmer3);
}

void dimmer3()
{
  // Aciona o triac e espera 200us para gerar a borda de descida
  digitalWrite(triac, HIGH);
  Timer1.stop();
}

