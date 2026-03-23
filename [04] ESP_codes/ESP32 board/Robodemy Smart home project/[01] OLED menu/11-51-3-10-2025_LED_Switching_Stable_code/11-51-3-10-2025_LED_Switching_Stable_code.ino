#include <Adafruit_SSD1306.h> 
Adafruit_SSD1306 display(128, 64, &Wire, -1); 
// Rotary Encoder Inputs
#define inputCLK 25
#define inputDT 26
#define encoderButtonPin 27


#define LED1 13
#define LED2 12
#define LED3 14


int encoderChange = 0;
int currentStateCLK;
int previousStateCLK;
int buttonPressed = false;
bool int_flag = 0;

String encdir = "";
//Interrupt service routine for encoder pins
void IRAM_ATTR encoderISR() {
  int_flag = 1;
}

unsigned long lastPress = millis(); 
//Interrupt service routine for button ins
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
 // lastPress = millis(); 
}

void setup() {
// Setup Serial Monitor
  Serial.begin(115200);
  if(display.begin(0x02, 0x3C)==0)
  {
    Serial.println("Display initialization failed!"); 
    while(1)
    {

    }
  }
  
  display.clearDisplay(); 
  display.setTextSize(2); 
  display.setTextColor(1); 
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT_PULLUP);
  pinMode(inputDT, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);
  //LED pins
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); 

 // digitalWrite(LED3, HIGH); 
  

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable

  previousStateCLK = digitalRead(inputCLK);

  attachInterrupt(inputCLK, encoderISR, CHANGE);
  attachInterrupt(encoderButtonPin, buttonISR, FALLING);
  //CHANGE - determines the change in the current state of the pin
  //FALLING - determines getting from HIGH to LOW
}
unsigned long lastClear = millis(); 

void loop() {
  // if (buttonPressed) {
  //   delay(200);
  //   Serial.println("Button Pressed");
  //   buttonPressed = false;
  // }

  
  display.setCursor(0, 0); 
  if(millis() - lastClear> 200)
  {
    display.clearDisplay(); 
    lastClear = millis(); 
  }


  byte p = panel(); 
      if(p==1) digitalWrite(LED1, HIGH); 
      if(p==2) digitalWrite(LED1, LOW); 
      if(p==3) digitalWrite(LED2, HIGH); 
      if(p==4) digitalWrite(LED2, LOW); 
      if(p==5) digitalWrite(LED3, HIGH); 
      if(p==6) digitalWrite(LED3, LOW); 
}
