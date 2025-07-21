const int FlameSensor = 2;
const int ledPin = 13;
const int buzzerPin = 11;

volatile bool flameDetectedFlag = false;  // Flag for interrupt

void setup() {
  pinMode(FlameSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);  // USART enabled for serial output

  // Set interrupt on FlameSensor (pin 2)
  attachInterrupt(digitalPinToInterrupt(FlameSensor), flameDetected, RISING);
}

void loop() {
  if (flameDetectedFlag) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);  // PWM for buzzer
    Serial.println("Flame Detected!");
    delay(500);  // Allow message to be visible and tone to last
    flameDetectedFlag = false;  // Reset flag
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    Serial.println("Safe - No Flame");
    delay(200);  // Check every 200ms
  }
}

// Interrupt Service Routine (ISR)
void flameDetected() {
  flameDetectedFlag = true;
}
