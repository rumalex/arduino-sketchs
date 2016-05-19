#include "Wire.h"
  #include "LiquidCrystal_I2C.h"

  LiquidCrystal_I2C lcd(0x27, 16, 2); //адрес 0x27 дисплей 16х2

   

  uint8_t tochki[8] = {B0, B00000, B0, B0, B0, B0, B10101};
  uint8_t bukva_P[8] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
  uint8_t bukva_Ya[8] = {B01111, B10001, B10001, B01111, B00101, B01001, B10001};
  uint8_t bukva_L[8] = {0x3, 0x7, 0x5, 0x5, 0xD, 0x9, 0x19};
  uint8_t bukva_Lm[8] = {0, 0, B01111, B00101, B00101, B10101, B01001};
  uint8_t bukva_Mz[8] = {0x10, 0x10, 0x10, 0x1E, 0x11, 0x11, 0x1E};
  uint8_t bukva_I[8] = {0x11, 0x13, 0x13, 0x15, 0x19, 0x19, 0x11};
  uint8_t bukva_D[8] = {B01111, B00101, B00101, B01001, B10001, B11111, 0x11};
  uint8_t bukva_G[8] = {B11111, B10001, B10000, B10000, B10000, B10000, B10000};
  int8_t bukva_IY[8] = {B01110, B00000, B10001, B10011, B10101, B11001, B10001};
  uint8_t bukva_Z[8] = {B01110, B10001, B00001, B00010, B00001, B10001, B01110};
  uint8_t bukva_ZH[8] = {B10101, B10101, B10101, B11111, B10101, B10101, B10101};
  uint8_t bukva_Y[8] = {B10001, B10001, B10001, B01010, B00100, B01000, B10000};
  uint8_t bukva_B[8] = {B11110, B10000, B10000, B11110, B10001, B10001, B11110};
  uint8_t bukva_CH[8] = {B10001, B10001, B10001, B01111, B00001, B00001, B00001};
  uint8_t bukva_IYI[8] = {B10001, B10001, B10001, B11001, B10101, B10101, B11001};
  uint8_t bukva_TS[8] = {B10010, B10010, B10010, B10010, B10010, B10010, B11111, B00001};

   

  void setup()

  {
    lcd.init();                      // инициализация LCD
    lcd.backlight();                 // включаем подсветку
    lcd.clear();                     // очистка дисплея
  }

  void loop() {
  vnesite(); delay (1000);
  avans(); delay (1000);
  gotov(); delay (1000);
  }

  void vnesite() {
    lcd.clear();
   lcd.createChar(0, bukva_I);  // создаем символы и записываем их в память LCD
    lcd.createChar(1, bukva_D);  lcd.createChar(2, bukva_Mz);
    lcd.createChar(3, bukva_G);  lcd.createChar(4, bukva_Lm);
    lcd.home();  lcd.print(" BHEC");  lcd.write(0);
    lcd.print("TE ");  lcd.write(1);  lcd.print("EH");
    lcd.write(2); lcd.write(3);  lcd.write(0);
    lcd.setCursor (0, 1); lcd.print("    ");
  }

   

  void avans() {
    lcd.clear();
    lcd.createChar(0, bukva_L);  lcd.createChar(1, bukva_IY);
    lcd.createChar(2, bukva_Lm);
    lcd.home();  lcd.print("ABAHC  ");
    lcd.setCursor (0, 1);  lcd.print("HA");  lcd.write(0); 
    lcd.print("E"); lcd.write(1);  lcd.print("TE ");
  }

   

  void gotov() {

    lcd.clear();
    lcd.createChar(0, bukva_L);  lcd.createChar(1, bukva_I);
    lcd.createChar(2, bukva_Z);  lcd.createChar(3, bukva_CH);
    lcd.createChar(4, bukva_P); lcd.createChar(5, bukva_B);
    lcd.home();  lcd.print(" HA"); lcd.write(0); lcd.write(1); lcd.print("B ");
    lcd.write(2);  lcd.print("AKOH"); lcd.write(3); lcd.print("EH");
    lcd.setCursor (0, 1);  lcd.print("    C"); lcd.write(4); lcd.print("AC");
    lcd.write(1); lcd.write(5); lcd.print("O");

  }
