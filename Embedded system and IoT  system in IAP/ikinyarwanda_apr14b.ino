#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN         22
#define SS_PIN          5
#define LED_PIN         2

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust if needed

bool ledState = false;

// Registered UIDs
byte uid_YK[4]       = { 0xDD, 0xDC, 0x31, 0x03 };
byte uid_HAZIZI[4]   = { 0x45, 0x89, 0xC8, 0x01 };
byte uid_OLIVIER[4]  = { 0x24, 0x86, 0xC8, 0x01 };
byte uid_DIVIN[4]    = { 0xFA, 0x31, 0x28, 0x03 };

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  Wire.begin(26, 27);         // SDA, SCL for I2C
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  ledState = false;

  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  lcd.clear();

  if (compareUID(uid_YK)) {
    // Toggle LED for YK
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    lcd.setCursor(0, 0);
    lcd.print("Hello: Chef YK");
    lcd.setCursor(0, 1);
    lcd.print(ledState ? "LED Turned ON" : "LED Turned OFF");
    Serial.println("YK: Toggle LED");

  } else if (compareUID(uid_HAZIZI)) {
    digitalWrite(LED_PIN, HIGH);
    ledState = true;
    lcd.setCursor(0, 0);
    lcd.print("Hello: HAZIZI");
    lcd.setCursor(0, 1);
    lcd.print("LED Turned ON");
    Serial.println("HAZIZI: LED ON");

  } else if (compareUID(uid_OLIVIER)) {
    digitalWrite(LED_PIN, HIGH);
    ledState = true;
    lcd.setCursor(0, 0);
    lcd.print("Hello: OLIVIER");
    lcd.setCursor(0, 1);
    lcd.print("LED Turned ON");
    Serial.println("OLIVIER: LED ON");

  } else if (compareUID(uid_DIVIN)) {
    digitalWrite(LED_PIN, HIGH);
    ledState = true;
    lcd.setCursor(0, 0);
    lcd.print("Hello: DIVIN");
    lcd.setCursor(0, 1);
    lcd.print("LED Turned ON");
    Serial.println("DIVIN: LED ON");

  } else {
    // UNKNOWN card: Turn LED OFF
    digitalWrite(LED_PIN, LOW);
    ledState = false;
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Unauthorized");
    Serial.println("Unknown card - LED OFF");
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Compare UID
bool compareUID(byte *knownUID) {
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != knownUID[i]) {
      return false;
    }
  }
  return true;
}

