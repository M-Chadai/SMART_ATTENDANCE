/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-gas-sensor
 */
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
#define AO_PIN A0 
 // Arduino's pin connected to AO pin of the MQ2 sensor
const int REDpin=13;
const int YellowPin=12;
const int greenPin= 11;
void setup() {
   lcd.init(); // initialize the lcd
  lcd.backlight(); // initialize serial communication
  pinMode(REDpin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  lcd.println("startUp");
  delay(2000);  // wait for the MQ2 to warm up
}

void loop() {
   int  gasValue= analogRead(AO_PIN);
 
  
  
  if(gasValue <= 80)
  {  
     lcd.clear();                 // clear display
  lcd.setCursor(0, 0);
    digitalWrite(greenPin,HIGH);
    digitalWrite(YellowPin,LOW);
    digitalWrite(REDpin,LOW);
    lcd.print("AO value: ");
    lcd.println(gasValue);
    
  }
  else if(gasValue >80 && gasValue <= 150)
  {
      lcd.clear();                 // clear display
  lcd.setCursor(0, 0);
    digitalWrite(YellowPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(REDpin,LOW);

    lcd.print("AO value: ");
    lcd.println(gasValue);
  }
  else
  {
      lcd.clear();                 // clear display
  lcd.setCursor(0, 0);
    digitalWrite(REDpin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(YellowPin,LOW);
    lcd.print("AO value: ");
    lcd.println(gasValue);
  }
delay(1000);
}

