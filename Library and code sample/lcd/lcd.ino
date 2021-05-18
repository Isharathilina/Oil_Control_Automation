//sketch created by Akshay Joseph
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup()
{

  lcd.begin();


  lcd.backlight();
  lcd.clear();
  lcd.setCursor(-4,3);
  lcd.print("Hackster");
  //lcd.print("ishara");
  //lcd.print("thilina");
}

void loop()
{
}
