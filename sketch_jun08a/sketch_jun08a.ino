
#include <EEPROM.h>
#include <Wire.h>
#include <DS1307.h>
#include "RTClib.h"
#define RELE_1 8 //объявляем работу 1 реле на пине 7
#define RELE_2 9 //объявляем работу 2 реле на пине 8

int FullMinutesTimerOn = EEPROM.read(0);
int FullMinutesTimerOff = EEPROM.read(2); 
int rtc[7];
byte rr[7];
};
// loop counter
int count = 0;



void setup () {

  pinMode(RELE_1, OUTPUT); //инициируем реле только на выход  
  pinMode(RELE_2, OUTPUT); //инициируем реле только на выход
  digitalWrite(RELE_1, HIGH); // запускаем реле выключенными
  digitalWrite(RELE_2, HIGH); // запускаем реле выключенными 
  
  RTC.get(rtc,true);
};

void loop () {
  int hourOn=EEPROM.read(110); //EEPROM.read(110)
  int hourOff= EEPROM.read(112);; //EEPROM.read(112)
  int minOn= EEPROM.read(111);; //EEPROM.read(111)
  int minOff= EEPROM.read(113);; //EEPROM.read(113)
  int minVent= EEPROM.read(114); //время работы вентилятора
  
  int Hour = rtc[2]; //присваиваем часы
  int Minute = rtc[1]; //присваиваем минуты
  int Second = rtc[0]; // присваиваем секунды
  int FullMinutes = Hour * 60 + Minute; //приводим значение текущего времени к минутам
  int FullMinutesTimerOn= hourOn*60+minOn; //приводим значение ВКЛЮЧЕНИЯ таймера к минутам
  int FullMinutesTimerOff= hourOff*60+minOff; //приводим значение ВЫКЛЮЧЕНИЯ таймера к минутам
  int sutki=0; // по умолчанию, таймер работает в одних сутках
  
  if (hourOff-hourOn < 0) sutki=1; //если время выключения на следующие сутки, то включаем триггер сутки=1
  else sutki=0;
    
  if (sutki==1 && (FullMinutes >= FullMinutesTimerOn || FullMinutes <= FullMinutesTimerOff) ) 
{
digitalWrite(RELE_1, LOW);
 // если сутки перескакивают, то проверяем время оператором ИЛИ
}
else if (sutki==1)
{
digitalWrite(RELE_1, HIGH);
}
  
  if (sutki == 0 && (FullMinutes >= FullMinutesTimerOn && FullMinutes <= FullMinutesTimerOff )) 
  {
digitalWrite(RELE_1, LOW);
  } // если сутки НЕ перескакивают, то проверяем время оператором И
  else if (sutki == 0) 
  {
digitalWrite(RELE_1, HIGH);
  }
  
  if ((Minute >= 0 && Minute <= minVent) && (Hour >= 9 && Hour <= 21))
  {
digitalWrite(RELE_2, LOW);
  }
  if (Minute >= 0 && Minute > minVent)
    {
digitalWrite(RELE_2, HIGH);
   }
  
  RTC.get(rtc,true);

if (rejim==0) 
  {
    lcd.setCursor(0, 2);
    lcd.print ("ojidayu komandi");
    }
     if (rejim==1) 
     {
      setTimerOn();
     }
   if (rejim==2) 
   {
      setTimerOff();
   }
  if (rejim==3) 
  {
      setTime();
    }
  if (rejim==4)
  {
  setVent();
  }  

if (digitalRead (button5) == HIGH) 
{ 
  rejim++;
  if (rejim>4) rejim=0;
  lcd.clear();
  //}
}
  
}

void setTimerOn() 
{
  int hourOn= EEPROM.read(110); 
  int minOn= EEPROM.read(111); 
  lcd.setCursor(0, 2);
  lcd.print("nastroika VKL");
  
      if (digitalRead(button3)==HIGH) //нажимая верхнюю кнопку меняем часы
     {  
      hourOn++;
      if (hourOn >=24) hourOn=0;
      }
   
  if (!digitalRead(button4)) //нажимая нижнюю кнопку меняем минуты
  {
    minOn++;
    if (minOn >=60) 
    {
      minOn=0;
      hourOn++;
      if (hourOn >=24) hourOn=0;
    }
    }
 strokatimera();
    if (digitalRead(button2) == HIGH)
    {
      EEPROM.write(110, hourOn);
      EEPROM.write(111, minOn);
      lcd.clear();
      }
    }

void setTimerOff() 
{
  int hourOff= EEPROM.read(112); 
  int minOff= EEPROM.read(113); 
  lcd.setCursor(0, 2);
  lcd.print("nastroika VIKL");
  
    if (digitalRead(button3)==HIGH) //нажимая верхнюю кнопку меняем часы
     {  
       hourOff++;
       if (hourOff >=24) hourOff=0;
      }
   
  if (!digitalRead(button4)) //нажимая нижнюю кнопку меняем минуты
  {
    minOff++;
    if (minOff >=60) 
    {
      minOff=0;
      hourOff++;
      if (hourOff >=24) hourOff=0;
     }
    }
 strokatimera();
    if (digitalRead(button2) == HIGH)
    {
      EEPROM.write(112, hourOff);
      EEPROM.write(113, minOff);
      lcd.clear();
      }
}

void setTime()
{
  int Hour = rtc[2]; //присваиваем часы
  int Minute = rtc[1];
  //lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print ("nastroika time");
  RTC.get(rtc,true);
  
  //lcd.setCursor(0, 3); // вывод в последней строчке времени работы таймера
   // lcd.print(Hour);
   // lcd.print(":");
   // lcd.print(Minute);
  
  if (!digitalRead(button4)) //нажимая нижнюю кнопку меняем минуты
  {
    Minute++;
    if (Minute >=60) 
    {
      Minute=0;
      Hour++;
      if (Hour >=24) Hour=0;
    }
   }
 
    if (digitalRead(button2) == HIGH)
    {
      RTC.set(DS1307_MIN,Minute);
      RTC.set(DS1307_HR,Hour);
      lcd.clear();
      }
  
   
}


    

