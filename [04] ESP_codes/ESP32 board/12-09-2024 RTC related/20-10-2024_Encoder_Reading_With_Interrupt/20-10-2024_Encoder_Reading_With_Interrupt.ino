#include <Wire.h>  // Library for I2C communication
#include <SPI.h>   // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS1307 RTC;  // Setup an instance of DS1307 naming it RTC

// Rotary Encoder Inputs
#define inputCLK 14   // CLK pin of the rotary encoder
#define inputDT 19    // DT pin of the rotary encoder
#define encoderButtonPin 23 // Button pin of the rotary encoder

volatile int counter = 0; // Using volatile because it will be changed in the ISR (Interrupt service routine)
volatile bool buttonPressed = false; // To handle the button press in the ISR

int currentStateCLK;
int lastCLKState;

void setup() {
  Wire.begin();  // Start the I2C communication
  RTC.begin();   // Initialize the RTC

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.println(F("SSD1306 allocation failed"));
    for (;;);  // Stop the program if OLED init fails
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(" Hi!  ");
  display.display();

  // Initialize encoder pins
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(encoderButtonPin, INPUT_PULLUP);  // Enable internal pull-up for the button

  // Set initial state of the CLK pin
  lastCLKState = digitalRead(inputCLK);

  // Attach interrupts for the encoder and button
  attachInterrupt(digitalPinToInterrupt(inputCLK), encoderISR, CHANGE);   // Interrupt on CLK pin change
  attachInterrupt(digitalPinToInterrupt(encoderButtonPin), buttonISR, FALLING);  // Interrupt on button press (FALLING edge)
}

void loop() {
  DateTime now = RTC.now();

  // Display the time on the OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.println();
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  display.println();

  // Display the encoder counter value
  display.println(counter);
  display.display();

  // Check if the button was pressed, reset the counter
  if (buttonPressed) {
    counter = 0;  // Reset counter
    buttonPressed = false;  // Reset flag
    delay(200);  // Debounce delay
  }

  delay(100);  // Small delay for display update
}

// Interrupt Service Routine (ISR) for the rotary encoder
void encoderISR() {
  // Read the current state of the CLK pin
  int currentStateCLK = digitalRead(inputCLK);

  // If the CLK pin has changed state
  if (currentStateCLK != lastCLKState) {
    // Check the DT pin to determine the direction
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;  // Counterclockwise rotation
    } else {
      counter++;  // Clockwise rotation
    }
    // Update the last known state of the CLK pin
    lastCLKState = currentStateCLK;
  }
}

// Interrupt Service Routine (ISR) for the button press
void buttonISR() {
  buttonPressed = true;  // Set the flag when the button is pressed
}
