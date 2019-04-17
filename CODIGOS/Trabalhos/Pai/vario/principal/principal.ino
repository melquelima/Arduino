#include <SFE_BMP180.h>
#include <Wire.h>
#include "filter.h"
#include "RunningMedian.h"

RunningMedian samples = RunningMedian(5);



AlphaBetaFilter filter(2.0, 2.0);
const float p0 = 101325;                 //Pressure at sea level (Pa)
SFE_BMP180   pressure;
long curr_pressure;
float curr_altitude;
float vario;
double baseline; // baseline pressure


void setup(){
  Wire.begin();
  Serial.begin(9600);
   if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
   Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

  baseline = getPressure();
 Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");  

  
}

void loop() {   
    curr_pressure = getPressure();//pressure.altitude(getPressure(), baseline);
//   bmp085.calcTruePressure(&curr_pressure);    
  // curr_altitude = (float)44330 * (1 - pow(((float)curr_pressure/p0), 0.190295)); 
   
     
   curr_altitude = pressure.altitude(getPressure(),baseline);
   samples.add(curr_altitude);
   filter.filter( samples.getMedian());
   
   vario = filter.getVelocity();
   Serial.print("vario: ");   
Serial.print(vario);
Serial.print(" ALT: ");
Serial.print( samples.getMedian(),1);
Serial.print(" MEDIAN: ");
Serial.print( samples.getCount(),1);
Serial.print(" LOWER: ");
Serial.println( samples.getLowest(),1);
delay(200);
curr_altitude = 0;
}



double getPressure()
{
  char status;
  double T,P,p0,a;

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

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

