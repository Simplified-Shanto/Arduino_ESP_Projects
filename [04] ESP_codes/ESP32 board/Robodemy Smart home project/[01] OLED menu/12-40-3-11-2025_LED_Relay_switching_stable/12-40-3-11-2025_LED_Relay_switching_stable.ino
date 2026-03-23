#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);
// Rotary Encoder Inputs
#define inputCLK 25
#define inputDT 26
#define encoderButtonPin 27


#define LED1 13
#define LED2 12
#define LED3 14
#define Relay 33


String options[8] = {
  "LED 1: Off          ",
  "LED 2: Off          ",
  "LED 3: Off          ",
  "Pump : Off          ",
  "Sensors             ",
  "------------        ",
  "------------        ",
  "------------        ",
};


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


//Interrupt service routine for button ins
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
  Serial.println("Button has been pressed"); 
  // lastPress = millis();
}

void setup() {
  // Setup Serial Monitor
  Serial.begin(115200);
  display.begin(0x02, 0x3C);
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
  pinMode(Relay, OUTPUT);
  // digitalWrite(LED3, HIGH);


  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable

  previousStateCLK = digitalRead(inputCLK);

  attachInterrupt(inputCLK, encoderISR, CHANGE);
  attachInterrupt(encoderButtonPin, buttonISR, FALLING);
  //CHANGE - determines the change in the current state of the pin
  //FALLING - determines getting from HIGH to LOW


 
}

boolean relayState = 0; 

void loop() {
  byte p = panel();
  if (p) {
    Serial.println(p);

      switch (p) {
        case 1:
          {
            if (digitalRead(LED1) == 1) {
              digitalWrite(LED1, LOW);
              options[0] = "LED 1: Off          ";
            } else {
              digitalWrite(LED1, HIGH);
              options[0] = "LED 1: On           ";
            }
          }
          break;
        case 2:
          {
            if (digitalRead(LED2) == 1) {
              digitalWrite(LED2, LOW);
              options[1] = "LED 2: Off          ";
            } else {
              digitalWrite(LED2, HIGH);
              options[1] = "LED 2: On           ";
            }
          }
          break;
        case 3:
          {
            if (digitalRead(LED3) == 1) {
              digitalWrite(LED3, LOW);
              options[2] = "LED 3: Off          ";
            } else {
              digitalWrite(LED3, HIGH);
              options[2] = "LED 3: On           ";
            }
          }
          break;
        case 4:
          {
            if (relayState ==1) {
              relayState = 0; 
              digitalWrite(Relay, LOW);
              options[3] = "Pump : Off          ";
            } else {
              relayState = 1; 
              digitalWrite(Relay, HIGH);
              options[3] = "Pump : On           ";
            }
          }
          break;
        case 5: 
          {
           //buttonPressed = false; 

            byte temp = showTemperature(); 
          } break; 

        default: break;
      }
      printMenu();
    
  }
}
