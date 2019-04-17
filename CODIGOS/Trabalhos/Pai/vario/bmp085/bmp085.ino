#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "BMP085.h"
#include "filter.h"

AlphaBetaFilter filter(2.0, 2.0);
const float p0 = 101325;                 //Pressure at sea level (Pa)
BMP085   bmp085 = BMP085();
long curr_pressure;
float curr_altitude;
float vario;

void setup(){
  Wire.begin();  
  bmp085.init(MODE_ULTRA_HIGHRES, p0, false);  
}

void loop() {   
   bmp085.calcTruePressure(&curr_pressure);    
   curr_altitude = (float)44330 * (1 - pow(((float)curr_pressure/p0), 0.190295)); 
   filter.filter(curr_altitude);
   vario = filter.getVelocity();   
}

