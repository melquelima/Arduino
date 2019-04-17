#include "HX711.h"

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

HX711 scale(A2, A3);		// parameter "gain" is ommited; the default value 128 is used by the library

double scal = 24;

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");
  scale.set_scale(scal);                      // this value is obtained by calibrating the scale with known weights; see the README for detail
  scale.tare();				        // reset the scale to 0

  Serial.println("Coloque o peso");
  delay(2000);
  calibragem(79000, 1000);
  Serial.println("Retire o peso");
  delay(5000);
  scale.tare();				        // reset the scale to 0

  Serial.println("Readings:");
}
//float calibraval[5] ={18,8,3,0.3,0.05};
//float calibraval[5] ={18,8,2,1,0.05};
float calibraval[5] ={1,0.3,0.1,0.05,0.005};

void calibragem(double peso, double rangee) {
  double vall = range(scale.get_units(10), rangee, peso);

  while (vall != 1) {
  
    scale.set_scale(scal);
    vall = range(scale.get_units(10), rangee, peso);
    
    if (vall < peso) {
      Serial.print("MENOR: "); Serial.print(vall); Serial.print(" - "); Serial.print(peso); Serial.print(" - Scale: "); Serial.println(scal, 4);
      scal = scal - (peso - vall > 10000 ? calibraval[0] : (peso - vall > 1000 ? calibraval[1] : (peso - vall > 15 ? calibraval[2] : (peso - vall > 4 ? calibraval[3] : calibraval[4]))));
      //scal = (scal < 0 ? scal * -1 : scal);
    } else {

      Serial.print("MAIOR: "); Serial.print(vall); Serial.print(" - "); Serial.print(peso); Serial.print(" - Scale: "); Serial.println(scal, 2);
      scal = scal + (vall - peso > 1000 ? calibraval[0] : (vall - peso > 100 ? calibraval[1] : (vall - peso > 15 ? calibraval[2] : (vall - peso > 4 ? calibraval[3] : calibraval[4]))));
    }
  }

}




double range(double val, double range, double peso) {
  double maximo = val + range;
  double minimo = val - range;

  return (peso <= maximo && peso >= minimo ? 1 : val);

}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(500);
  scale.power_up();
}
