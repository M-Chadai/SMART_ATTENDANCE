#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set LCD I2C address — usually 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 LCD

String voiceCommand = "";

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // Relay OFF by default (active LOW)

  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting voice...");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    voiceCommand += c;
    delay(2);
  }

  voiceCommand.trim(); // Clean up command

  if (voiceCommand.length() > 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Command: ");
    lcd.setCursor(0, 1);
    lcd.print(voiceCommand);

    delay(1000); // Short delay to display command

    if (voiceCommand == "turn on") {
      digitalWrite(13, LOW); // Turn lamp ON (active LOW)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lamp Status:");
      lcd.setCursor(0, 1);
      lcd.print("   TURNED ON");
    } 
    else if (voiceCommand == "turn off") {
      digitalWrite(13, HIGH); // Turn lamp OFF (active LOW)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lamp Status:");
      lcd.setCursor(0, 1);
      lcd.print("  TURNED OFF");
    } 
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid Cmd:");
      lcd.setCursor(0, 1);
      lcd.print(voiceCommand);
    }

    delay(2000); // Show result before resetting
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting voice...");
    voiceCommand = ""; // Reset command
  }
}
