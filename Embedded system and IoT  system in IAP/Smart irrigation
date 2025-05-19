#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHT11_PIN A10
#define DHTTYPE DHT11
#define MOISTURE_PIN A1

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C address, 16 columns, 2 rows
DHT dht11(DHT11_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht11.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float humi  = dht11.readHumidity();
  float tempC = dht11.readTemperature();
  int moistureValue = analogRead(MOISTURE_PIN);

  lcd.clear();

  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read DHT11!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
  } else {
    // Display on Serial Monitor
    Serial.print("Temp: ");
    Serial.print(tempC);
    Serial.print("°C | Humidity: ");
    Serial.print(humi);
    Serial.print("% | Moisture: ");
    Serial.println(moistureValue);

    // Display on LCD
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(tempC);
    lcd.print("C H:");
    lcd.print(humi);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("Moist:");
    lcd.print(moistureValue);
  }

  delay(2000);
}
