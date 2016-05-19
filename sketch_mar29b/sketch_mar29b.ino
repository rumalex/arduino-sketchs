#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h> 
//Подключаемые бибилиотеки

LiquidCrystal_I2C lcd(0x27,16,2);  // LCD Задаем объект lcd c адресом 0x27 количество символов в строке 16 и количество строк 2

int button = 2; //номер ноги куда подключена кнопка управления

int pol0 = 0;
int pol1 = 1;
int pol2 = 2;

long tim; // переменная для хранения времени в секундах с начала эпохи UNIX

int sensorPin = A0;    // Нога подключения аналогового сенсора
int sensorValue = 0;  // Зачение уровня сигнала аналогового сенсора




void setup() //начальные установки
{
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT); // декларируем вход аналогового сенсора
  
TimeElements tm; //переменная-объект хранения времени
  
  attachInterrupt(0, ButtonUp, RISING); // Включение обработки нулевого внешнего прерывания (всего прерываний на uno два (0 и 1) соответсвенно ноги 2 и 3
  // detachInterrupt(0); //Выключение обработки нулевого прерывания
  pinMode(button, INPUT); // Включаем прослушивание на 2 ноге
  
  lcd.init();                      // инициализируем LCD
  lcd.backlight();                 // включаем подсветку
      
  Serial.begin(9600);              // задаем скорость компорта
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  
  setSyncProvider(RTC.get);   // Синхронизируем время с DS1307
  //setTime(8,29,0,1,1,11);   // Можем задать и свое (ч м с д м г)
  
  if(timeStatus()!= timeSet)  // Проверяем статаус часов
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");


  tim = now(); //глобальной переменной присваиваем время начала работы

 
 // Задаем время для тревог и таймеров
 
 tm.Year = 2016 - 1970;//(offset from 1970)
 tm.Month = 4;
 tm.Day = 6;
 tm.Hour = 0;
 tm.Minute = 19;
 tm.Second = 0; 
 Alarm.triggerOnce(makeTime(tm),RedAlarm2); //http://www.cy-pr.com/tools/time/ 
  
   //Alarm.alarmRepeat(21,52,0, RedAlarm);  // 8:30am every day
  //Alarm.alarmOnce(20,48,30,RedAlarm);  // 5:45pm once day 
  //Alarm.alarmRepeat(dowMonday,21,33,00,RedAlarm);  // 8:30:30 every Saturday 
  //Alarm.timerRepeat(15, RedAlarm);            // timer for every 15 seconds    
  //Alarm.timerOnce(10, RedAlarm);  
}


void loop() {
long tm; 
// read the value from the sensor:
  sensorValue = analogRead(sensorPin);  // снимаем сигнал аналогового сенсора
  sensorValue = map(sensorValue, 0, 1023, 0, 100);




  
if (timeStatus() == timeSet) {

    if (pol0 < 2) PrintDate(pol0);
    if (pol1 < 2) PrintTime(pol1);
    //if (pol2 < 2) PrintMetr(pol2);
     if (pol2 < 2) PrintValue(pol2);
    //lcd.setCursor(0,1);
    //lcd.print(now());
    
  } else {
    lcd.setCursor(0,0);
    lcd.print("The time has");
    lcd.setCursor(0,1);
    lcd.print("not been set");
    
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }

Serial.println(sensorValue);  // выводим уровень датчика в  компорт
tm = Alarm.getNextTrigger();
Serial.println(year(tm));
Serial.println(month(tm));
Serial.println(day(tm));
Serial.println(hour(tm));
Serial.println(minute(tm));
Serial.println(second(tm));


Serial.println(Alarm.getNextTrigger());
Serial.println(Alarm.count());
Serial.println(Alarm.read(1));
Serial.println(Alarm.read(2));
Serial.println(Alarm.read(3));
Serial.println(Alarm.read(4));
Serial.println(Alarm.read(5));


Serial.println(ClockDate() + " " + ClockTime());
Alarm.delay(200);
}

void PrintValue(int num) {

    lcd.setCursor(0,num);
    lcd.print("VALU:  ") ;
    lcd.print(sensorValue);
    lcd.print("            ") ;
 }

void PrintDate(int num) {

if (timeStatus() == timeSet) {
    lcd.setCursor(0,num);
    lcd.print("DATE: ") ;
    lcd.print(ClockDate());
    lcd.print(" ") ;
  }
}



void PrintTime(int num) {

if (timeStatus() == timeSet) {
    lcd.setCursor(0,num);
    lcd.print("TIME:  ") ;
    lcd.print(ClockTime());
    lcd.print(" ") ;
  }
}

void PrintMetr(int num) {
long vim;
long btw;
int scd;
int mnt;
int hou;
int dny;
if (timeStatus() == timeSet) {
    lcd.setCursor(0,num);
    lcd.print("INTE:") ;
   // lcd.print(now()-tim);
   btw = now() - tim ;
   scd = btw % 60;
   mnt = ((btw - scd)/60) % 60;
   hou = ((btw - scd - mnt*60)/3600) % 24;
   dny = (btw - scd - mnt*60 - hou*3600)/86400;
   
   lcd.print(DigToStr(dny));
   lcd.print("/");
   lcd.print(DigToStr(hou)); 
   lcd.print(":");  
   lcd.print(DigToStr(mnt));
   lcd.print(":");
   lcd.print(DigToStr(scd));
   lcd.print("         ") ;
  }
}







String ClockDate(){
  // digital clock display of the time
String str = "00/00/0000";
str = DigToStr(day()) + "/" + DigToStr(month()) + "/" + String(year());
return str;  
}

String ClockTime(){
  // digital clock display of the time
String str = "00:00:00";
str = DigToStr(hour()) + ":" + DigToStr(minute()) + ":" + DigToStr(second());
return str;   
}

String DigToStr(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
String str = "00";
 if(digits < 10) {
  str = "0" + String(digits);
  return str;
 } else {
  str = String(digits);
  return str; 
}
}

void ButtonUp()
{
switch (pol0) {
   case 0:
      pol0=2;
      pol1=0;
      pol2=1;
      break;
   case 1:
      pol0=0;
      pol1=1;
      pol2=2;
      break;
   case 2:
      pol0=1;
      pol1=2;
      pol2=0;
      break;
  }
//Serial.println("");
//Serial.println(pol0);
//Serial.println(pol1);
}


///
// functions to be called when an alarm triggers:
void RedAlarm(){
  Serial.println("Alarm:" + ClockDate() + " " + ClockTime());    
}

void RedAlarm2(){
  Serial.println("Alarm!!!!:" + ClockDate() + " " + ClockTime()); 
  //Alarm.write(3,20);
  Alarm.timerRepeat(15, RedAlarm);    
}



