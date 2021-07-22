#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define sensorPin A0
LiquidCrystal_I2C lcd(0x27, 16, 2); 
int led1=10;
int led2=11;
int led3=12;
int signalpin =2;
int signalpin2=3;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TEMP");
  lcd.setCursor(6,0);
  lcd.print("HEATER");
  lcd.setCursor(6,1);
  lcd.print("OF");
  lcd.setCursor(13,0);
  lcd.print("FAN");
  lcd.setCursor(13,1);
  lcd.print("OF");
   
}
void loop() {
 int reading = analogRead(sensorPin);
  float voltage = reading * (5000 / 1024.0);
  float temperature = voltage / 10;
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); 
  Serial.println("C");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  delay(2000); 
  if (temperature<24){
  digitalWrite(led1, 1); 
  digitalWrite(led2, 0);
  digitalWrite(led3,0);
  lcd.setCursor(6,1);
  lcd.print("ON");
  }
  else if (temperature>24&&temperature<25){
     digitalWrite(led1, 0);
     digitalWrite(led2, 1);
     digitalWrite(led3, 0); 
     lcd.setCursor(6,1);
     lcd.print("OF");
     lcd.setCursor(13,1);
     lcd.print("OF");
    }
    else if (temperature>25)
    {
     digitalWrite(led1, 0);
     digitalWrite(led2, 0);
     digitalWrite(led3, 1); 
     lcd.setCursor(13,1);
     lcd.print("ON");
      }
      else{
        digitalWrite(led1, 0);  
        digitalWrite(led2, 0); 
        digitalWrite(led3, 0);
        lcd.setCursor(6,1);
        lcd.print("OF");
        lcd.setCursor(13,1);
        lcd.print("OF");
        }
}
