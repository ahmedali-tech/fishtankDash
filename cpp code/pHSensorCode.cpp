#include<LiquidCrystal.h>
const int rs =13,en = 12,d4 =11,d5 =10,d6 =9,d7 =8;
LiquidCrystal lcd(rs,en, d4,d5,d6,d7);
int Contrast = 0;
void setup()
{
  Serial.begin(9600);
  analogWrite (6,Contrast);
  lcd.begin(16,2);
  lcd.setCursor(4,0);
  lcd.print("pH Value:");
}

void loop()
{
 int sensorValue = analogRead(A0);
 float ph = sensorValue * (14.0/1023.0);
 Serial.println(ph);
 lcd.setCursor(6,1);
 lcd.print (ph);
}

