#include <Wire.h>
#include <SPI.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS1307 RTC;

// Rotary Encoder Inputs
#define inputCLK 14
#define inputDT 19
#define encoderButtonPin 23

// Encoder variables
volatile int counter = 0;
volatile bool buttonPressed = false;
int lastCLKState;

// Clock and Date variables
int second, minute, hour, day, date, month, year;
int settingIndex = -1;  // -1 means no setting mode, otherwise it represents the setting being modified

void setup() {
  Wire.begin();
  RTC.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }

  // Initialize encoder pins
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(encoderButtonPin, INPUT_PULLUP);

  lastCLKState = digitalRead(inputCLK);

  // Attach interrupts for the encoder and button
  attachInterrupt(digitalPinToInterrupt(inputCLK), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderButtonPin), buttonISR, FALLING);

  DateTime now = RTC.now();
  second = now.second();
  minute = now.minute();
  hour = now.hour();
  day = now.dayOfTheWeek();
  date = now.day();
  month = now.month();
  year = now.year();
}

void loop() {
  if (settingIndex == -1) {
    // Normal time display mode
    DateTime now = RTC.now();
    second = now.second();
    minute = now.minute();
    hour = now.hour();
    day = now.dayOfTheWeek();
    date = now.day();
    month = now.month();
    year = now.year();

    displayTimeAndDate();
  } else {
    // Settings mode: Blink the selected setting
    blinkSetting(settingIndex);
  }

  if (buttonPressed) {
    handleButtonPress();
    buttonPressed = false;
  }

  delay(200);  // Small delay to reduce flickering
}

void displayTimeAndDate() {
  display.clearDisplay();
  
  // Display Date (Day, Date, Month, Year) at the top in small font
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(dayOfWeek(day)); display.print(", ");
  display.print(date); display.print(" ");
  display.print(monthName(month)); display.print(" ");
  display.print(year);
  display.println();

  // Display Hour and Minute in big font (central)
  display.setTextSize(2);
  display.setCursor(30, 25);
  display.print(hour);
  display.print(":");
  display.print(minute);

  // Display Second in small font at the corner
  display.setTextSize(1);
  display.setCursor(110, 50);
  display.print(second);

  display.display();
}

// Interrupt Service Routine for the encoder
void encoderISR() {
  int currentStateCLK = digitalRead(inputCLK);
  
  if (currentStateCLK != lastCLKState) {
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
    } else {
      counter++;
    }
    
    // Update the selected setting based on the encoder rotation
    if (settingIndex != -1) {
      adjustSetting(settingIndex, counter);
    }
    
    lastCLKState = currentStateCLK;
  }
}

// Interrupt Service Routine for the button press
void buttonISR() {
  buttonPressed = true;
}

// Handle button presses: cycle through settings or exit settings mode
void handleButtonPress() {
  settingIndex++;
  if (settingIndex > 6) {
    // Save changes and exit settings mode
    settingIndex = -1;
    saveSettings();
  }
}

// Adjust the current setting (hour, minute, etc.)
void adjustSetting(int index, int value) {
  switch (index) {
    case 0: second = (second + value) % 60; break;
    case 1: minute = (minute + value) % 60; break;
    case 2: hour = (hour + value) % 24; break;
    case 3: day = (day + value) % 7; break;
    case 4: date = (date + value) % 31 + 1; break;
    case 5: month = (month + value) % 12 + 1; break;
    case 6: year += value; break;
  }
}

// Blink the setting being modified
void blinkSetting(int index) {
  static unsigned long lastBlinkTime = 0;
  static bool blinkState = true;

  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime > 500) {
    blinkState = !blinkState;
    lastBlinkTime = currentTime;
  }

  display.clearDisplay();
  
  // Display the date
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(dayOfWeek(day)); display.print(", ");
  display.print(date); display.print(" ");
  display.print(monthName(month)); display.print(" ");
  display.print(year);
  display.println();

  // Blink the setting based on `index`
  display.setTextSize(2);
  if (index == 2) {
    if (blinkState) {
      display.setCursor(30, 25);
      display.print(hour);
      display.print(":");
      display.print(minute);
    }
  } else if (index == 1) {
    display.setCursor(30, 25);
    display.print(hour);
    if (blinkState) {
      display.print(":");
      display.print(minute);
    }
  }
  // Display second in small font
  display.setTextSize(1);
  if (index != 0 || blinkState) {
    display.setCursor(110, 50);
    display.print(second);
  }

  display.display();
}

// Save settings to RTC after changes
void saveSettings() {
  RTC.adjust(DateTime(year, month, date, hour, minute, second));
}

// Helper functions
String dayOfWeek(int day) {
  const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  return days[day];
}

String monthName(int month) {
  const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return months[month];
}
