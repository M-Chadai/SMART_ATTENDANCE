// Define PIR sensor pin
const int pirPin = 2;     // PIR sensor OUT pin connected to digital pin 2
const int ledPin = 13;    // Optional: use built-in LED to indicate motion

void setup() {
  pinMode(pirPin, INPUT);     // Set PIR pin as input
  pinMode(ledPin, OUTPUT);    // Set LED pin as output

  Serial.begin(9600);         // Start serial communication
  Serial.println("PIR Sensor Test Ready...");
}

void loop() {
  int pirState = digitalRead(pirPin);  // Read PIR sensor value

  if (pirState == HIGH) {
    Serial.println("Motion Detected!");
    digitalWrite(ledPin, LOW);        // Turn on LED
  } else {
    Serial.println("No Motion");
    digitalWrite(ledPin, HIGH);      // Turn off LED
  }

  delay(250);  // Small delay to avoid flooding serial monitor
}
