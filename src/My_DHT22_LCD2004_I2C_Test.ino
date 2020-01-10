/*
  LCD Display with I2C Interface Demo
  lcd-i2c-demo.ino
  Use NewLiquidCrystal Library
  DroneBot Workshop 2018
  https://dronebotworkshop.com

  Edited by ZeFerby using LCD2004/I2C + DHT22
*/
#include <Arduino.h>

// DHT-22
#include "dht_nonblocking.h"
// Uncomment according to your sensortype.
//#define DHT_SENSOR_TYPE DHT_TYPE_11
//#define DHT_SENSOR_TYPE DHT_TYPE_21
#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = 7;

// LCD 2004

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
 
// Define LCD I2C Address - change if required
const int i2c_addr = 0x27;
 
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);


DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );



void setup( )
{
  // Set display type as 20 chars, 4 rows
  lcd.begin(20,4);
  
  // Clear the display
  lcd.clear();
  lcd.noBacklight();
  delay(500);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print( "Temp.  : " );
  lcd.setCursor(0, 1);
  lcd.print( "Humid. : " );
  lcd.setCursor(0, 2);
  lcd.print( "Snd.Sp.: " );
}



/*
 * Poll DHTxx for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}


float temp;
float hum;
float soundsp;
int nCnt = 0;

void loop( )
{
  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temp, &hum ) == true )
  {
    lcd.setCursor(9, 0);
    lcd.print( temp, 1 );
    lcd.print( " C     " );
    lcd.setCursor(9, 1);
    lcd.print( hum, 1 );
    lcd.print( " %     " );

    // Calculate the Speed of Sound in m/s
    soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);

    lcd.setCursor(9, 2);
    lcd.print( soundsp );
    lcd.print( " m/s " );

    lcd.setCursor(0, 3);
    nCnt++;
    if (nCnt > 100000) { nCnt = 1; lcd.print( "       " ); }
    lcd.print(nCnt);
  }
}
