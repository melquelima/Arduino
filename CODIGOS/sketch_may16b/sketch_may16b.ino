int sensor= 0;


void setup()
{
  Serial.begin(9600);
}

void loop()
{
int sensorReading = analogRead(sensor); 
Serial.println(sensorReading);
delay(500);
}
