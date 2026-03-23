/*
Intended board: ESP Wroom 32

Description: In this version we'll increment a number on the oled display
by rotating the encoder. 
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
#define inputCLK 14  // of ESP WROOM 32
#define inputDT 19   // of ESP WROOM 32
#define encoderButtonPin 23

int counter = 0;
int currentStateCLK;
int previousStateCLK;

// Clock and Date variables
int second, minute, hour, day, date, month, year;
int settingIndex = -1;  // -1 means no setting mode, otherwise it represents the setting being modified

void setup() {

  Wire.begin();  // Start the I2C
  RTC.begin();   // Init RTC

  //  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(" Hi!  ");
  display.display();

  //Encoder pinouts
  pinMode(inputCLK, INPUT); 
  pinMode(inputDT, INPUT); 
  pinMode(encoderButtonPin, INPUT_PULLUP);

  previousStateCLK = digitalRead(inputCLK);
}

void loop() {
  if(settingIndex==-1)
  {
  displayTimeAndDate(); 
  }
}


void displayTimeAndDate()
{
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

// Helper functions
String dayOfWeek(int day) {
  const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  return days[day];
}

String monthName(int month) {
  const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return months[month];
}

