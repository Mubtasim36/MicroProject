int LED = 13;              // LED pin
int Flame_sensor = 3;      // Flame sensor digital output pin
int Buzzer = 11;           // Buzzer pin
int Flame_detected;        // Stores the sensor reading

void setup()
{
  Serial.begin(9600);              // Start Serial Monitor
  pinMode(LED, OUTPUT);            // Set LED pin as OUTPUT
  pinMode(Buzzer, OUTPUT);         // Set Buzzer pin as OUTPUT
  pinMode(Flame_sensor, INPUT);    // Set flame sensor pin as INPUT
}

void loop()
{
  Flame_detected = digitalRead(Flame_sensor);  // Read sensor
  Serial.print("Flame_detected = ");
  Serial.println(Flame_detected);

  if (Flame_detected == LOW)  // Flame detected (LOW signal)
  {
    Serial.println("Flame detected...! Take action immediately.");
    digitalWrite(LED, HIGH);       // Turn on LED
    digitalWrite(Buzzer, HIGH);    // Turn on Buzzer
  }
  else
  {
    Serial.println("No Flame detected. Stay cool.");
    digitalWrite(LED, LOW);        // Turn off LED
    digitalWrite(Buzzer, LOW);     // Turn off Buzzer
  }

  delay(500);  // Delay for readability and debounce
}
