int inPin = 10;
 
void setup()
{
   Serial.begin(9600);
   pinMode(inPin, INPUT);
}
 
void loop()
{
    int valor = digitalRead(inPin);
 
  Serial.println((valor == 1? "Preto":"Branco"));
}
