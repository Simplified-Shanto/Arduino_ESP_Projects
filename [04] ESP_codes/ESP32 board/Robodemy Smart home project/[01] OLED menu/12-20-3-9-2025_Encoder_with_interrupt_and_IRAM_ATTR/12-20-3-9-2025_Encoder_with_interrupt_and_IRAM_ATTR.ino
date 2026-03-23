// Rotary Encoder Inputs
#define inputCLK 25
#define inputDT 26
#define encoderButtonPin 27


int counter = 0;
int currentStateCLK;
int previousStateCLK;
int buttonPressed = false;
bool int_flag = 0;

String encdir = "";
//Interrupt service routine for encoder pins
void IRAM_ATTR encoderISR() {
  int_flag = 1;
}

//Interrupt service routine for button ins
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
}
void setup() {

  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT_PULLUP);
  pinMode(inputDT, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(115200);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable

  previousStateCLK = digitalRead(inputCLK);

  attachInterrupt(inputCLK, encoderISR, CHANGE);
  attachInterrupt(encoderButtonPin, buttonISR, FALLING);
  //CHANGE - determines the change in the current state of the pin
  //FALLING - determines getting from HIGH to LOW
}

void loop() {
  if (buttonPressed) {
    delay(200);
    Serial.println("Button Pressed");
    buttonPressed = false;
  }

  if (int_flag) {
    int_flag = 0;
    // Read the current state of inputCLK
    currentStateCLK = digitalRead(inputCLK);

    // If the previous and the current state of the inputCLK are different then a pulse has occured
    if (currentStateCLK != previousStateCLK) {
      // If the inputDT state is different than the inputCLK state then
      // the encoder is rotating counterclockwise
      if (digitalRead(inputDT) != currentStateCLK) {
        counter--;
        encdir = "CCW";
      } else {
        // Encoder is rotating clockwise
        counter++;
        encdir = "CW";
      }
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);
    }
    // Update previousStateCLK with the current state
    previousStateCLK = currentStateCLK;
  }
}
