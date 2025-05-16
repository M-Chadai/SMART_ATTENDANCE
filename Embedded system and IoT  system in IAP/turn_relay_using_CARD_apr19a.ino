#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN     9     // RST pin of RC522
#define SS_PIN      10    // SDA pin of RC522
#define RELAY_PIN   2     // Relay connected to D2

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address if needed

bool relayState = false;

// Registered UIDs
byte uid_YK[4]       = { 0xDD, 0xDC, 0x31, 0x03 };
byte uid_HAZIZI[4]   = { 0x45, 0x89, 0xC8, 0x01 };
byte uid_OLIVIER[4]  = { 0x24, 0x86, 0xC8, 0x01 };
byte uid_DIVIN[4]    = { 0xFA, 0x31, 0x28, 0x03 };

void setup() {
  Serial.begin(9600);
  SPI.begin();             // Init SPI bus
  rfid.PCD_Init();         // Init RC522

  lcd.init();
  lcd.backlight();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with relay OFF
  relayState = false;

  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  lcd.clear();

  if (compareUID(uid_YK)) {
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
    lcd.setCursor(0, 0);
    lcd.print("Hello: YK");
    lcd.setCursor(0, 1);
    lcd.print(relayState ? "Relay Turned ON" : "Relay Turned OFF");
    Serial.println("YK toggled relay");

  } else if (compareUID(uid_HAZIZI)) {
    digitalWrite(RELAY_PIN, HIGH);
    relayState = true;
    lcd.setCursor(0, 0);
    lcd.print("Hello: HAZIZI");
    lcd.setCursor(0, 1);
    lcd.print("Relay Turned ON");
    Serial.println("HAZIZI turned ON relay");

  } else if (compareUID(uid_OLIVIER)) {
    digitalWrite(RELAY_PIN, HIGH);
    relayState = true;
    lcd.setCursor(0, 0);
    lcd.print("Hello: OLIVIER");
    lcd.setCursor(0, 1);
    lcd.print("Relay Turned ON");
    Serial.println("OLIVIER turned ON relay");

  } else if (compareUID(uid_DIVIN)) {
    digitalWrite(RELAY_PIN, HIGH);
    relayState = true;
    lcd.setCursor(0, 0);
    lcd.print("Hello: DIVIN");
    lcd.setCursor(0, 1);
    lcd.print("Relay Turned ON");
    Serial.println("DIVIN turned ON relay");

  } else {
    digitalWrite(RELAY_PIN, LOW);
    relayState = false;
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Unauthorized");
    Serial.println("Unknown UID - relay OFF");
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Compare UID function
bool compareUID(byte *knownUID) {
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != knownUID[i]) {
      return false;
    }
  }
  return true;
}
