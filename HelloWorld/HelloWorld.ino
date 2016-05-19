//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <DS1307RTC.h>
#define DS1307_ADDRESS 0x68
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HELLO, world!");
  lcd.setCursor(0,1);
  lcd.print("Ywrobot Arduino!");
}


void loop()
{
 Wire.beginTransmission(0x68);
 tmElements_t tm;
 if (RTC.read(tm)) {
 Serial.println(tm.Second);
 lcd.setCursor(0,1);
 lcd.print(tm.Second);
 delay(600);
 }
 else {
 lcd.setCursor(0,1);
 lcd.print("22222");
 }
 delay(100);
  
}
