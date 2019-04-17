#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <BMP085.h>
#include "filter.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int deltaAlt = 0;
int playBeep = 1;
#define DIS_SIZE 9
#define DIS_MAIN 0
#define DIS_CALIBREALT 1
#define DIS_MAXRISE 2
#define DIS_MAXALT 3
#define DIS_BEEP_RISE 4
#define DIS_BEEP_SINK 5
#define DIS_CAL_ALPHA 6
#define DIS_CAL_BETA  7
#define DIS_CAL_TONE  8
#define DIS_CAL_LIGHT  9
long update_dis = 0;
int curr_dis = DIS_MAIN;

float max_rise = 0;
float max_alt = 0;

float vario_start_up = 0.4;
float vario_start_down = -1.1;
#define NPRES    10
#define NSAMPLES 40
#define TONE1 9
#define TONE2 8
#define ROWS 1 //four rows
#define COLS 4 //three columns
char keys[ROWS][COLS] = {
    {'-', '+','S','B'},
    
};

byte rowPins[ROWS] = {8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13,10,6,7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

AlphaBetaFilter filter(1.0, 1.0);
const float p0 = 101325;                 //Pressure at sea level (Pa)
BMP085   bmp085 = BMP085();
float alt[NSAMPLES];
long t[NSAMPLES];
float St, Sa, Sta, Stt;
float pres[NPRES];
long t0;
int ant = 0;

int c = 0;
float altitude;
long curr_pressure;
float curr_altitude;
float curr_vario;
long temperature;
long pressure;
long time_vario;
float vario, vario2;
long  itime, beep, beep_period;
int i;

byte v[7][8] = {{
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
},
{
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
},
{
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
},
{
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
}, 
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
},
{
  B10000,
  B11000,
  B11100,
  B11110,
  B11100,
  B11000,
  B10000,
},
{
  B00000,
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
}
};

long meanPresure(long in) // moving average filter function
{
  float sum = 0;
  for (int i = 1; i < NPRES; i++) {
    pres[i-1] = pres[i];
    sum += pres[i-1];
  }
  pres[NPRES - 1] = in;
  sum += in;
  return ( sum / NPRES) ;
}

void setup(){
  
  tone( TONE1, 880, 200 );
  delay( 280 );
  tone( TONE1, 1070, 300 );
  delay( 180 );
  
  keypad.addEventListener(keypadEvent);
  Wire.begin();
  lcd.begin(16, 2);
  beep_period = 0;
  beep = 0;
  for(int i = 0; i < 7; i++ )
      lcd.createChar(i, v[i]);
  
  pinMode(1,OUTPUT); //define o pino como saída 
  digitalWrite(1,LOW); // Liga a luz do display.
  
  bmp085.init(MODE_ULTRA_HIGHRES, p0, false);  
  bmp085.calcTruePressure(&curr_pressure); 
  curr_altitude = (float)44330 * (1 - pow(((float)curr_pressure/p0), 0.190295));
  t0 = millis();
  for(i=0; i < NSAMPLES; i++) {
       t[i] = t0;
       alt[i] = curr_altitude;
  }
 
}

void loop() {
   
   char k = keypad.getKey();
   
     
  
   t0 = millis();
  
   bmp085.calcTruePressure(&curr_pressure); 
   
   curr_altitude = (float)44330 * (1 - pow(((float)curr_pressure/p0), 0.190295)); 
   c++;
   filter.filter(curr_altitude);
   vario = filter.getVelocity();
   if( vario > max_rise )
     max_rise = vario;
   if( t0 - beep > beep_period ) {
       beep = t0;
       if( playBeep )
         beep_period = playTone( vario );                          
      
   }


   if( (t0 - time_vario) > 1000 && curr_dis == DIS_MAIN   ) {

     
      bmp085.getTemperature(&temperature);
      temperature /= 10.0;
      time_vario = t0;
      lcd.clear();
      lcd.setCursor(0,0);
      
       
      if( abs(vario) > 0.2 ) {
   
        if( vario > 0 )
            lcd.print("+");   
        lcd.print(vario, 1);
        
        
        
      } else {
        lcd.print("+0.0");
      } 
      lcd.print("m/s");
      
      lcd.setCursor(0,1);
      curr_altitude = round(filter.getPosition()) + deltaAlt;
      lcd.print(curr_altitude,0 );
      if( curr_altitude > max_alt )
          max_alt = curr_altitude;
      lcd.print("m ");

      lcd.print( temperature );
      lcd.write(byte(6));

      if( vario > 0 ) {      
        lcd.setCursor(8,1);
        int ncharsfull = vario;
        
        for(int k = 0; k <  ncharsfull; k++ ) {
             lcd.setCursor(8+k,0);
             lcd.write(byte(4));  
             lcd.setCursor(8+k,1);
             lcd.write(byte(4));  
             
        }
        int n = (vario*10) - ((int)vario*10);
        n /= 2;
        if( n > 0 ) {
          lcd.setCursor(8+ncharsfull, 0);
          lcd.write(byte(n-1));
          lcd.setCursor(8+ncharsfull, 1);
          lcd.write(byte(n-1));
          
//          lcd.write(byte(5));  
        } else {
  //        lcd.setCursor(8+ncharsfull, 1);
  //        lcd.write(byte(5));
        }
      }
        
      ant = c;
   } else if(t0 - update_dis > 150 ) { 
     update_dis = t0;
  
     if( curr_dis == DIS_CALIBREALT ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ALT. CALIBRATION");
        lcd.setCursor(0,1);
        lcd.print( round(filter.getPosition()) + deltaAlt );
        lcd.print("m");
     } else if( curr_dis == DIS_MAXRISE ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MAX. RISE");
        lcd.setCursor(0,1);
        lcd.print("+");
        lcd.print(max_rise, 1);
        lcd.print("m/s");
     }else if( curr_dis == DIS_MAXALT ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MAX. ALTITUDE");
        lcd.setCursor(0,1);
        lcd.print(max_alt, 0);
        lcd.print("m");
     } else if( curr_dis == DIS_BEEP_RISE ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BEEP START RISE");
        lcd.setCursor(0,1);
        lcd.print("+");
        lcd.print(vario_start_up, 1);
        lcd.print("m/s");
     } else if( curr_dis == DIS_BEEP_SINK ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BEEP START SINK");
        lcd.setCursor(0,1);
        lcd.print(vario_start_down, 1);
        lcd.print("m/s");
     } else if( curr_dis == DIS_CAL_ALPHA ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ALPHA CALIBRAT.");
        lcd.setCursor(0,1);
        lcd.print(filter.getAlpha(), 1);
        
     } else if( curr_dis == DIS_CAL_BETA ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BETA CALIBRAT.");
        lcd.setCursor(0,1);
        lcd.print(filter.getBeta(), 1);
        
     } else if( curr_dis == DIS_CAL_TONE ) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ENABLE BEEP");
        lcd.setCursor(0,1);
        if( playBeep == 1) lcd.print("ON");
        else lcd.print("OFF");
        
        
     } 
   }
}


int playTone( float vario ) {
    if (vario>vario_start_up && vario<=10 ) {
        tone(TONE1, (500+(60*vario)),360-(vario*(20+vario))); 
        return 470-(vario*(20+vario));
    } else if( vario > 10 ) {
      tone(TONE1, 3450,80);                          //spike climb rate
      return 100;
    } else if( vario < vario_start_down ) {
      tone(TONE1, 300,340);
      return 200;  
    }
}

void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '+' && curr_dis == DIS_CALIBREALT) {
          deltaAlt++;    
        }
        if (key == '-' && curr_dis == DIS_CALIBREALT) {
          deltaAlt--;    
        }
        
        if (key == '+' && curr_dis == DIS_BEEP_RISE) {
          
          vario_start_up = vario_start_up + 0.1;
              
        }
        if (key == '-' && curr_dis == DIS_BEEP_RISE) {
          if( vario_start_up >= 0.1 )
            vario_start_up = vario_start_up - 0.1;  
        }
        
        if (key == '+' && curr_dis == DIS_BEEP_SINK) {
          if( vario_start_down <= -0.1 )
            vario_start_down = vario_start_down + 0.1;
              
        }
        if (key == '-' && curr_dis == DIS_BEEP_SINK) {
          
            vario_start_down = vario_start_down - 0.1;  
        }
        
        if (key == '+' && curr_dis == DIS_CAL_ALPHA) 
            filter.setAlpha(   filter.getAlpha() + 0.1 );   
        
        if (key == '-' && curr_dis == DIS_CAL_ALPHA)
           filter.setAlpha(   filter.getAlpha() - 0.1 );
        
        if (key == '+' && curr_dis == DIS_CAL_BETA) 
            filter.setBeta(   filter.getBeta() + 0.1 );   
        
        if (key == '-' && curr_dis == DIS_CAL_BETA)
           filter.setBeta(   filter.getBeta() - 0.1 );
         
        if ((key == '+' || key == '-') && curr_dis == DIS_CAL_TONE) 
            playBeep = (playBeep + 1) % 2;   
        
        if (key == '-' && curr_dis == DIS_CAL_BETA)
           filter.setBeta(   filter.getBeta() - 0.1 );  
           
        
        if( key == 'S') {
           curr_dis=(curr_dis+1) % DIS_SIZE;
               
        }
        
         if( key == 'B') {
           curr_dis=0;
               
        }
        break;
    }

}
