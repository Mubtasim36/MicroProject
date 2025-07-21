const int FlameSensor = 2; 
const int ledPin      = 13;
const int buzzerPin   = 11;

void setup() {
  pinMode(FlameSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int sensorState = digitalRead(FlameSensor);

  if (sensorState == HIGH) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // 1 kHz tone
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin); // Stop the tone
  }

  delay(50);
}