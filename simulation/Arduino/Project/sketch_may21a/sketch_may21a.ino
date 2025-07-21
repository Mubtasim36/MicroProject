
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

const int relay1 = 12;  // motor1 forward 12
const int relay2 = 14;  // motor1 backward 14
const int relay3 = 26;  // motor2 forward 26
const int relay4 = 27;  // motor2 backward 27
const int pumpRelay = 33; // pump control 33

bool pumpActive = false;
unsigned long pumpStartTime = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("NeoMatrix"); // Bluetooth device name

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(pumpRelay, OUTPUT);

  // All OFF initially (active LOW relays)
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(pumpRelay, HIGH);  // pump OFF
}

void loop() {
            while (SerialBT.available()) {  // this is for hardware
           char receivedChar = SerialBT.read();// this is for hardware
    Serial.println("Received: " + String(receivedChar));
    handleBluetoothData(receivedChar);
  }

  // Auto turn off pump after 2 seconds
  if (pumpActive && (millis() - pumpStartTime >= 2000)) {
    digitalWrite(pumpRelay, HIGH); // OFF
    pumpActive = false;
    Serial.println("Pump auto turned OFF after 2 seconds");
  }
}

void handleBluetoothData(char data) {
  switch (data) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'G':
      forwardLeft();
      break;
    case 'I':
      forwardRight();
      break;
    case 'H':
      backwardLeft();
      break;
    case 'J':
      backwardRight();
      break;
    case 'S':
      stopMotors();
      break;
    case 'W': // Pump ON for 2 seconds
      digitalWrite(pumpRelay, LOW);  // ON
      pumpStartTime = millis();
      pumpActive = true;
      Serial.println("Pump turned ON");
      break;
    default:
      stopMotors();
      break;
  }
}

// Motor control functions
void moveForward() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  Serial.println("Moving forward");
}

void moveBackward() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  Serial.println("Moving backward");
}

void turnLeft() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  Serial.println("Turning left");
}

void turnRight() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  Serial.println("Turning right");
}

void forwardLeft() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  Serial.println("Forward left");
}

void forwardRight() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  Serial.println("Forward right");
}

void backwardLeft() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  Serial.println("Backward left");
}

void backwardRight() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  Serial.println("Backward right");
}

void stopMotors() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  Serial.println("Motors stopped");
}
