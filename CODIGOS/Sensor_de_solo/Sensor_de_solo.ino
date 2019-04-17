//define analog inputs to which we have connected our sensors
int moistureSensor = 0;
//define variables to store moisture
int moisture_val;
// define variable for rele pump water
int rele_pump = 13;

void setup() {
//open serial port
Serial.begin(9600);
//define o pino 13 como saida e que vai acionar a bomba de agua
pinMode(rele_pump, OUTPUT);
Serial.println("Bem vindo ao SaveGarden version 1.0");
Serial.print("created by Renan Rider");

}
void loop() {
teste();
// read the value from the moisture-sensing probes, print it to screen, and wait 500 milisecond
moisture_val = analogRead(moistureSensor);
Serial.print("moisture sensor: ");
Serial.println( moisture_val );
delay(500);
}

void teste(){
//OBS: leitura maxima do sensor 905
//solo humido
if(moisture_val > 300){

Serial.println("solo humido");
}

//solo normal
if(moisture_val < 290 && moisture_val > 190){
Serial.println("solo normal");
}
if(moisture_val < 180){

Serial.println("solo seco");
digitalWrite(rele_pump, HIGH);
delay(10000);
digitalWrite(rele_pump, LOW);
}
}
