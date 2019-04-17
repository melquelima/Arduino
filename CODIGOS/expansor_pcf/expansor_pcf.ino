#include <Wire.h>

void setup() {
Wire.begin();
Wire.beginTransmission(0x20);
  Wire.write(B00000000);
  Wire.endTransmission();

}

void loop() {
Wire.beginTransmission(0x20);
  Wire.write(B11111110);
  Wire.endTransmission();
  delay(100);
  
  Wire.beginTransmission(0x21);
  Wire.write(B11110110);
  Wire.endTransmission();
  delay(100);
  
  
}
