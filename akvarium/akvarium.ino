#include <Wire.h>
#include "RTClib.h"
#include "Time.h"

#define RELE_1 9
#define RELE_2 8

#define ON 0
#define OFF 1


RTC_Millis rtc;

void setup(){
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));

  digitalWrite(RELE_1, OFF); 
  digitalWrite(RELE_2, OFF);   
  pinMode(RELE_1, OUTPUT);   
  pinMode(RELE_2, OUTPUT); 

  Serial.begin(9600);
}

void loop(){
  //printing the current time
  DateTime now = rtc.now();
  Serial.print(now.year());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.day());
  Serial.print(' ');
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();
   
  //if ((now.hour() >= 8 && now.hour() <= 11 ) || (now.hour() >= 13 && now.hour() <= 17 ) || (now.hour() >= 19 && now.hour() <= 22 ))  
  if ((now.hour() >= 22 && now.hour() <= 23 ) && (now.minute() >= 5 && now.minute() <= 50 ))   {
    // turn RELAY on:
    digitalWrite(RELE_1, ON);
  }
  else {
    // turn RELAY off:
    digitalWrite(RELE_1, OFF);
  }
  
 if ((now.hour() >= 8 && now.hour() <= 21 ) && (now.minute() >= 0 && now.minute() <= 50 ))  {
    // turn RELAY on:
    digitalWrite(RELE_2, ON);
  }
  else {
    // turn RELAY off:
    digitalWrite(RELE_2, OFF);
  } 
  
 delay(10000); 
}


