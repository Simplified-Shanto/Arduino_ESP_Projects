// Rotary Encoder Inputs
#define inputCLK 25
#define inputDT 26
#define encoderButtonPin 12


int counter = 0;
int currentStateCLK;
int previousStateCLK;
int buttonPressed = false; 

String encdir = "";

void setup() {

  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
   pinMode(encoderButtonPin, INPUT_PULLUP); 

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  
  previousStateCLK = digitalRead(inputCLK);

  attachInterrupt(digitalPinToInterrupt(inputCLK), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderButtonPin), buttonISR, FALLING);
  //CHANGE - determines the change in the current state of the pin
  //FALLING - determines getting from HIGH to LOW
 
}

void loop() {
  if(buttonPressed)
  {
    delay(200); 
    Serial.println("Button Pressed"); 
    buttonPressed = false; 
  }
}


//Interrupt service routine for encoder pins
void encoderISR() {
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

//Interrupt service routine for button ins
void buttonISR() {
  buttonPressed = true; 
}
