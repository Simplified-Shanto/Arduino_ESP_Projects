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

   6. You have to set the hour in 24 hour format, but it'll be displayed 
      24 hour format. 
   7. Year is not displayed in this version, but you need to set it 
      because, leap year is taken into considerationi for calculating
      day and dates.  
   6. Upon pressing the shaft button at the last parameter (second)
      the clock will exit the settings mode and you'll bu in point
      1. 
*/


#include <Wire.h> //V:   // Library for I2C communication
#include <SPI.h>  //V:  // not used here, but needed to prevent a RTClib compile error
#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
//#include <Fonts/FreeSansBold12pt7b.h>  // Smaller font
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DS3231 rtc;
RTCDateTime now;

// Rotary Encoder Inputs
#define inputCLK 14          // CLK pin of the rotary encoder
#define inputDT 19           // DT pin of the rotary encoder
#define encoderButtonPin 23  // Button pin of the rotary encoder

volatile int counter = 0;             // Using volatile because it will be changed in the ISR (Interrupt service routine)
volatile bool buttonPressed = false;  // To handle the button press in the ISR

int currentStateCLK;
int lastCLKState;

int second, minute, hour, date, month, year;
//Index 0     1       2     3     4      5

void setup() {
  Wire.begin();  // Start the I2C communication
  rtc.begin();   // Initialize the RTC
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


int settingIndex = -1;  // -1 means no setting mode, otherwise it represents the setting being modified


void loop() {

  if (settingIndex == -1) {
    displayTimeAndDate();
  } else {
    blinkSetting(settingIndex);
  }

  if (buttonPressed) {
    if (settingIndex == -1)                       //If we are currently displaying time, then we will check longpress
    {                                             //in the following mechanism.
      if (digitalRead(encoderButtonPin) == HIGH)  //If the button has been pressed shortly and released,
      {
        buttonPressed = false;  //                  then we'll unflag buttonPressed
        Serial.println("Short press!");
      } else if (millis() - lastPress > 2000) {  //If the button is still being pressed then check if it is a long press.
        Serial.println("Long press detected!");
        lastPress = millis();
        buttonPressed = false;
        handleButtonPress();
      }
    } else {
      handleButtonPress();
      buttonPressed = false;
    }
  }
  // Serial.println(settingIndex);
  // blinkSetting(settingIndex);
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
  display.setFont(NULL);
  // Display the date
  display.setTextSize(1);

  display.setCursor(30, 0);
  if (index != 0) {
    display.print(date);
  } else if (blinkState) { // index = 0, we are changing this value right now, and blinkstate = 1. 
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

 // display.println();
 // display.setTextSize(2);
  // display.setCursor(30, 25);

  // if (index != 3) {
  //   display.print(hour);
  // } else if (blinkState) {
  //   display.print(hour);
  // }
  // display.setCursor(70, 25);
  // display.print(":");
  // if (index != 4) {
  //   display.print(minute);
  // } else if (blinkState) {
  //   display.print(minute);
  // }

  // // Display Second in small font at the corner
  // display.setTextSize(1);
  // display.setCursor(110, 50);
  // if (index != 5) {
  //   display.print(second);
  // } else if (blinkState) {
  //   display.print(second);
  // }


  display.display();
}

void displayTimeAndDate() {
  now = rtc.getDateTime();

  //DateTime now = RTC.now();
  second = now.second;
  minute = now.minute;
  hour = now.hour;
  //day = now.day;
  date = now.day;
  month = now.month;
  year = now.year;
  display.clearDisplay();

  display.setFont(NULL);
  display.setCursor(1, 1);
  display.setTextSize(2);
  display.println(rtc.dateFormat("D M d", now));

  display.setTextSize(2);
  display.setCursor(100, 45);
  display.println(rtc.dateFormat("s", now));

  display.setFont(&FreeSans9pt7b);
  display.setCursor(-8, 55);
  //display.setTextSize(2);
  display.println(rtc.dateFormat(" h:i", now));  //h - 12 hour format/ H - 24 hour format

  display.display();
}


String monthName(int month) {
  const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
  return months[month];
}



// int second, minute, hour, day, date, month, year;
// //Index 5     4       3          0     1      2
// int settingIndex = -1;  // -1 means no setting mode, otherwise it represents the setting being modified
// Display Hour and Minute in big font (central)

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
        case 3: hour = (hour + counter) % 25; break;  //Time counting and settings will be done in 24 hour format, but
                                                      //during displaying time, it'll be converted to 12 hour format.
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
  Serial.print("Setting Index = "); 
  Serial.println(settingIndex); 
}

void saveSettings() {
  //rtc.setDateTime(2024, 9, 12, 3, 34, 30);
  rtc.setDateTime(year, month + 1, date, hour, minute, second);
}
