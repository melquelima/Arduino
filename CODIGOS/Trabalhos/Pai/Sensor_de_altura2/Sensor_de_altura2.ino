#include <SFE_BMP180.h>
#include <Wire.h>
#include <TimerOne.h>

// You will need to create an SFE_BMP180 object, here called "pressure":



SFE_BMP180 pressure;

double baseline; // baseline pressure
long anterior = 0;
int buzz = 11;
double aceleracao = 0;
double aceleracaoant = 0;
boolean entra = false;


void setup()
{
  Timer1.initialize(10000);
  Timer1.attachInterrupt( timerIsr );
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while (1); // Pause forever.
  }

  // Get the baseline pressure:

  baseline = getPressure();

  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");
}

void loop()
{
  aceleracao = get_mps();
  Serial.println(aceleracao, 1);
}

double get_mps() {
  double a, P;
  double a2, P2;
  for (int i = 1; i <= 5; i++) {
    P = getPressure();
    a = a + pressure.altitude(P, baseline);
  }
  a = a / 5;
  delay(1000);

  for (int i = 1; i <= 5; i++) {
    P2 = getPressure();
    a2 = a2 + pressure.altitude(P2, baseline);
  }
  a2 = a2 / 5;
  aceleracao = (!entra ? (a2 - a) : aceleracao);
  aceleracaoant = (entra ? (a2 - a) : aceleracaoant);
  entra = !entra;
  Serial.print("1 = "); Serial.print(aceleracao); Serial.print(" 2 = "); Serial.println(aceleracaoant);
  return (a2 - a);
}


double getPressure()
{
  char status;
  double T, P, p0, a;

  // You must first get a temperature measurement to perform a pressure reading.

  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          return (P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

boolean ativabuzz = false;
void timerIsr()
{
  int tempo;
  if (aceleracao > 0.6 && aceleracaoant > 0.6) {
    tempo = map(aceleracao, 0.6, 15, 400, 0);
    tempo = (aceleracao >= 15 ? 50 : tempo);
    ativabuzz = true;
  } else {
    digitalWrite(buzz, 0);
    ativabuzz = false;
  }
  long current = millis();
  if ((current - anterior > tempo) && ativabuzz) {
    digitalWrite(buzz, !digitalRead(buzz));
    anterior = current;
  }

}
