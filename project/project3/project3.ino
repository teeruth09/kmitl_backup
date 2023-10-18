const int IR_LED_PIN = 7;   // IR LED pin
const int IR_RECEIVER_PIN = A5;  // IR receiver pin
const int BUZZER_PIN = 8;  // Buzzer pin
const int DEBOUNCE_DELAY = 50; // Debounce delay in milliseconds

int debounceAnalogRead(int pin) {
  int val = analogRead(pin);
  delay(DEBOUNCE_DELAY);
  int newVal = analogRead(pin);
  if (abs(val - newVal) < 10) {
    return newVal;
  } else {
    return val;
  }
}

void setup() {
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(IR_RECEIVER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Send IR signal
  Serial.println(analogRead(IR_RECEIVER_PIN));
  digitalWrite(IR_LED_PIN, HIGH);
  delayMicroseconds(100);  // Replace with your desired IR signal timing
  digitalWrite(IR_LED_PIN, LOW);
  delay(10);  // Wait for receiver to settle

  // Read status of IR receiver with debouncing
  int receiverValue = debounceAnalogRead(IR_RECEIVER_PIN);

  // If the receiver value is high, turn on the buzzer
  if (receiverValue > 500) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Buzzer ON");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Buzzer OFF");
  }

  delay(100);  // Replace with your desired loop delay
}
