/*
  Arduino Nano - 1 direction motor speed control with potentiometer
  Pot wiper  -> A7
  RPWM       -> D5  (PWM)
  LPWM       -> D3  (kept LOW)

  Note: DHT on D2 is present but not used here.
*/

const int POT_PIN  = A7;
const int RPWM_PIN = 5;   // D5
const int LPWM_PIN = 3;   // D3

// Optional: small deadzone so the motor fully stops near the "off" end
const int DEADZONE = 15;  // 0..1023 (increase if your motor still spins slightly)

void setup() {
  pinMode(RPWM_PIN, OUTPUT);
  pinMode(LPWM_PIN, OUTPUT);

  digitalWrite(LPWM_PIN, LOW);   // force one direction
  analogWrite(RPWM_PIN, 0);      // start stopped
}

void loop() {
  int pot = analogRead(POT_PIN);           // 0..1023

  // Apply deadzone near 0 so extreme end = guaranteed stop
  if (pot < DEADZONE) pot = 0;

  int pwm = map(pot, 0, 1023, 0, 150);     // 0..255
  analogWrite(RPWM_PIN, pwm);              // speed control

  // keep the other direction off
  digitalWrite(LPWM_PIN, LOW);

  delay(5); // small smoothing delay
}