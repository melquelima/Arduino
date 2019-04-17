int AC_LOAD = 3;    // Output to Opto Triac pin
int dimming = 3;  // Dimming level (0-128)  0 = ON, 128 = OFF
int A = 13;
int B= 12;
int C= 11;
int D= 10;
void setup()
{
  pinMode(AC_LOAD, OUTPUT);// Set AC Load pin as output
  attachInterrupt(0, zero_crosss_int, RISING);  // Choose the zero 
  pinMode(A,INPUT_PULLUP);
  pinMode(B,INPUT_PULLUP);
  pinMode(C,INPUT_PULLUP);
  pinMode(D,INPUT_PULLUP);
  Serial.begin(9600);
}

void zero_crosss_int()
{
  int dimtime = (520*dimming);    // For 60Hz =>65    
  delayMicroseconds(dimtime);    // Wait till firing the TRIAC  	
  digitalWrite(AC_LOAD, HIGH);   // Fire the TRIAC
  delayMicroseconds(8.33);         // triac On propogation delay 
				 // (for 60Hz use 8.33) Some Triacs 
  digitalWrite(AC_LOAD, LOW);    // No longer trigger the TRIAC (the 

}

void loop()  {
 // int valor =(digitalRead(A)*8)+(digitalRead(B)*4) + (digitalRead(C)*2) + (digitalRead(D)*1); 
 //  dimming = (valor == 0?1:valor);
//Serial.println(dimming);
}
