#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX

void setup()  
{
  mySerial.begin(9600);
  delay(500);
}

void loop() // run over and over
{
    mySerial.println("$");
    delay(5);
}

