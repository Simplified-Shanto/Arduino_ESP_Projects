/*
  Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com

  Last used board: JRC board (esp wroom 32); worked fine 
  the following 3 pins of the board. This pin configuration
  might have to be changed for other esp boards or arduino. 
  



*/

// Rotary Encoder Inputs
#define inputCLK 14  // of ESP WROOM 32
#define inputDT 19   // of ESP WROOM 32
#define encoderButtonPin 23

int counter = 0;
int currentStateCLK;
int previousStateCLK;

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
}


long long lastPrint = millis();
void loop() {

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);


  //Test code for making sure the code is running.
  // if (millis() - lastPrint > 3000) {
  //   Serial.println("Code is running!");
  //   lastPrint = millis();
  // }



  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
      encdir = "CCW";
      //  digitalWrite(ledCW, LOW);
      //  digitalWrite(ledCCW, HIGH);
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);

    } else {
      // Encoder is rotating clockwise
      counter++;
      encdir = "CW";
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);
    }
    // previousStateCLK = currentStateCLK;
  }
  //  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;

  if(digitalRead(encoderButtonPin)==0)
  {
  
    Serial.println("Button Pressed!"); 
      delay(200);  //Debounce time. 
  }


}