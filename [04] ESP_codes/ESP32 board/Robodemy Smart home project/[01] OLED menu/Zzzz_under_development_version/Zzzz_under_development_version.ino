#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

Servo doorServo; 
#define servoPin 14
Adafruit_SSD1306 display(128, 64, &Wire, -1);
// Rotary Encoder Inputs
#define inputCLK 25
#define inputDT 26
#define encoderButtonPin 27


#define LED1 13
#define LED2 12
#define Relay 33


#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 5
#define RST_PIN 2




MFRC522 rfid(SS_PIN, RST_PIN);
String authorizedUID = "b3 53 59 28";  // Replace with your RFID card UID

void initializeRFID() {
  SPI.begin();
  rfid.PCD_Init();
}

String options[8] = {
  "LED 1: Off          ",
  "LED 2: Off          ",
  "Doors: Closed       ",
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


byte identificationStatus = 0;

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
  initializeServo(); 
  display.begin(0x02, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("Put RFID card: ");
  display.display();
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT_PULLUP);
  pinMode(inputDT, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);
  //LED pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Relay, OUTPUT);
  // digitalWrite(LED3, HIGH);


  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable

  previousStateCLK = digitalRead(inputCLK);

  attachInterrupt(inputCLK, encoderISR, CHANGE);
  attachInterrupt(encoderButtonPin, buttonISR, FALLING);
  //CHANGE - determines the change in the current state of the pin
  //FALLING - determines getting from HIGH to LOW

  initializeRFID();
  
}

boolean relayState = 0, doorState = 0;

void loop() {
  if (identificationStatus == 0) {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
      return;
    }
    String readUID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      readUID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      readUID += String(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) readUID += " ";
    }

    Serial.print("Card UID: ");
    Serial.println(readUID);

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    if (readUID.equalsIgnoreCase(authorizedUID)) {
      identificationStatus = 1;
      display.println("Access granted");
      Serial.println("Access granted");
    } else {
      display.println("Access denied");
      Serial.println("Access denied");
    }
    display.display();

    delay(2000);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

  } else {
    // Serial.println(identificationStatus);
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
             if(doorState==1)
            {
              closeDoor(); 
            } else {
              openDoor(); 
            }
          }
          break;
        case 4:
          {
            if (relayState == 1) {
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
            byte temp = showTemperature();
          }
          break;

        default: break;
      }
      printMenu();
    }
  }
}

#define openAngle  150
#define closeAngle  90
#define angleChangeDelay 30

void initializeServo()
{
  // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	doorServo.setPeriodHertz(50);    // standard 50 hz servo
	doorServo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
  doorServo.write(closeAngle); 
}


void closeDoor()
{
  for (int pos = openAngle; pos >= closeAngle; pos -= 1) { 
		doorServo.write(pos);    
		delay(angleChangeDelay); 
  } 
  options[2] = "Doors: Closed       "; 
  doorState = 0;            
}

void openDoor()
{
  for (int pos = closeAngle; pos <= openAngle; pos+=1) { 
		doorServo.write(pos);    
		delay(angleChangeDelay); 
  }  
  options[2] = "Doors: Open         "; 
  doorState = 1;           
}
