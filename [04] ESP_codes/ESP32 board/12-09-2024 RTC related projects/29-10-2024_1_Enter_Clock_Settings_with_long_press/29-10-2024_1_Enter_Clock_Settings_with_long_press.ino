/* Code modified and maintained by : Md. Nayeem Islam Shanto
   Contact: islamnayeem386@gmail.com

   Last used board: ESP WROOM 32. 
   Hardwares: 
   1. ESP WROOM 32
   2. 128x64 monochrome OLED display
   3. HW040 rotary encoder. 
   4. DS3231 Real Time Clock module. 

   Functions: 
   1. On powering up, you can see day, date, month and year on top
      Hour and minute in the middle and second on the bottom right
      corner. 
   2. How to adjust time and date?  -> Keep pressing the encoder
      shaft button for 2 seconds at a stretch for enterning into 
      the settings. Then the parameter subject to change will keep
      blinking. 
   3. Turn the encoder knob clockwise for incrementing
      the value of the parameter by one for one small step of the 
      encoder. 
      
   4. Turn counterclockwise for decresing the value of the parameter
      by one. 

   5. Press the encoder shaft button once for moving to the next 
      parameter. 
   6. Upon pressing the shaft button at the last parameter (second)
      the clock will exit the settings mode and you'll bu in point
      1. 
*/




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
#define inputCLK 14          // CLK pin of the rotary encoder
#define inputDT 19           // DT pin of the rotary encoder
#define encoderButtonPin 23  // Button pin of the rotary encoder

volatile int counter = 0;             // Using volatile because it will be changed in the ISR (Interrupt service routine)
volatile bool buttonPressed = false;  // To handle the button press in the ISR

int currentStateCLK;
int lastCLKState;

int second, minute, hour, day, date, month, year;
//Index 0     1       2          3     4      5
int settingIndex = -1;  // -1 means no setting mode, otherwise it represents the setting being modified

void setup() {
  Wire.begin();  // Start the I2C communication
  RTC.begin();   // Initialize the RTC
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Stop the program if OLED init fails
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
  attachInterrupt(digitalPinToInterrupt(inputCLK), encoderISR, CHANGE);          // Interrupt on CLK pin change
  attachInterrupt(digitalPinToInterrupt(encoderButtonPin), buttonISR, FALLING);  // Interrupt on button press (FALLING edge)
}

long lastPress = millis();  //Timer variable used for detecting long press.

void loop() {

  if (settingIndex == -1) {
    displayTimeAndDate();
  } else {
    blinkSetting(settingIndex);


    // display.print(counter);
    // display.setCursor(20, 50);
    // display.print(settingIndex);
    // display.setCursor(110, 50);
    // display.display();
  }

  if (buttonPressed) {

    if (settingIndex == -1)                       //If we are currently displaying time, then we will check longpress
    {                                             //in the following mechanism.
      if (digitalRead(encoderButtonPin) == HIGH)  //If the button has been pressed shortly and released,
      {
        buttonPressed = false;  //                  then we'll unflag buttonPressed
      } else if (millis() - lastPress > 2000) {   //If the button is still being pressed then check if it is a long press. 
        lastPress = millis();
        buttonPressed = false;
        handleButtonPress();
      }
      Serial.println(lastPress);
    } else {
      handleButtonPress();
      buttonPressed = false;
    }
  }

  //display.clearDisplay();
  // display.print(counter);
  // display.setCursor(20, 50);
  // display.print(settingIndex);
  // display.setCursor(110, 50);
  // display.display();
}

// Blink the setting being modified
void blinkSetting(int index) {
  static unsigned long lastBlinkTime = 0;
  static bool blinkState = true;

  // unsigned long currentTime = millis();
  if (millis() - lastBlinkTime > 250) {
    blinkState = !blinkState;
    lastBlinkTime = millis();
  }



  display.clearDisplay();
  // Display the date
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(dayOfWeek(day));
  display.print(", ");


  display.setCursor(30, 0);
  if (index != 0) {
    display.print(date);
  } else if (blinkState) {
    display.print(date);
  }


  display.setCursor(50, 0);
  if (index != 1) {
    display.print(monthName(month));
  } else if (blinkState) {
    display.print(monthName(month));
  }

  display.setCursor(80, 0);

  if (index != 2) {
    display.print(year);
  } else if (blinkState) {
    display.print(year);
  }

  display.println();
  display.setTextSize(2);
  display.setCursor(30, 25);

  // int second, minute, hour, day, date, month, year;
  // //Index 5     4       3          0     1      2
  // int settingIndex = -1;  // -1 means no setting mode, otherwise it represents the setting being modified

  // Display Hour and Minute in big font (central)
  if (index != 3) {
    display.print(hour);
  } else if (blinkState) {
    display.print(hour);
  }
  display.setCursor(70, 25);
  display.print(":");
  if (index != 4) {
    display.print(minute);
  } else if (blinkState) {
    display.print(minute);
  }

  // Display Second in small font at the corner
  display.setTextSize(1);
  display.setCursor(110, 50);
  if (index != 5) {
    display.print(second);
  } else if (blinkState) {
    display.print(second);
  }



  display.display();
}

void displayTimeAndDate() {
  DateTime now = RTC.now();

  //DateTime now = RTC.now();
  second = now.second();
  minute = now.minute();
  hour = now.hour();
  day = now.dayOfTheWeek();
  date = now.day();
  month = now.month();
  year = now.year();


  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  // Display Date (Day, Date, Month, Year) at the top in small font
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(dayOfWeek(day));
  display.print(", ");
  display.setCursor(30, 0);
  display.print(date);
  display.print(" ");
  display.setCursor(50, 0);
  display.print(monthName(month));
  display.print(" ");
  display.setCursor(80, 0);
  display.print(year);
  display.println();

  // Display Hour and Minute in big font (central)
  display.setTextSize(2);
  display.setCursor(30, 25);
  display.print(hour);
  display.print(":");
  display.setCursor(70, 25);
  display.print(minute);

  // Display Second in small font at the corner
  display.setTextSize(1);
  display.setCursor(110, 50);
  display.print(second);


  display.display();
}
// Helper functions
String dayOfWeek(int day) {
  const char* days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
  return days[day];
}

String monthName(int month) {
  const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
  return months[month];
}



// Interrupt Service Routine (ISR) for the rotary encoder
void encoderISR() {
  // Read the current state of the CLK pin
  int currentStateCLK = digitalRead(inputCLK);
  // int second, minute, hour, day, date, month, year;
  // //Index 5     4       3          0     1      2
  // If the CLK pin has changed state
  if (currentStateCLK != lastCLKState) {
    // Check the DT pin to determine the direction
    if (digitalRead(inputDT) != currentStateCLK) {
      counter = 1;  // Clockwise rotation
      switch (settingIndex) {
        case 5: second = (second + counter) % 60; break;
        case 4: minute = (minute + counter) % 60; break;
        case 3: hour = (hour + counter) % 13; break;
        case 0: date = (date + counter) % 32; break;
        case 1: month = (month + counter) % 12; break;
        case 2: year += counter; break;
        default: break;
      }
    } else {
      counter = -1;  // Counterclockwise rotation
      switch (settingIndex) {
        case 5: second = max(0, second + counter); break;
        case 4: minute = max(0, minute + counter); break;
        case 3: hour = max(0, hour + counter); break;
        case 0: date = max(0, date + counter); break;
        case 1: month = max(0, month + counter); break;
        case 2: year = max(0, year + counter); break;
        default: break;
      }
    }
  }
  // Update the last known state of the CLK pin
  lastCLKState = currentStateCLK;
}

// Interrupt Service Routine (ISR) for the button press
void buttonISR() {
  lastPress = millis();
  buttonPressed = true;  // Set the flag when the button is pressed
  Serial.println("It's pressing!");
}
// Handle button presses: cycle through settings or exit settings mode
void handleButtonPress() {
  settingIndex++;
  delay(200);
  if (settingIndex > 5) {
    // Save changes and exit settings mode
    settingIndex = -1;
    saveSettings();
  }
}

void saveSettings() {
  RTC.adjust(DateTime(year, month, date, hour, minute, second));
}
