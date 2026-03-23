#include <Wire.h> // Library for I2C communication
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


 
RTC_DS1307 RTC;     // Setup an instance of DS1307 naming it RTC
 
void setup () 
{
 // display.begin(57600); // Set display port speed
 // lcd.begin();
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC

//  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
 // display.print("Time and date set");
  // lcd.setCursor(0, 0);
  // lcd.print("Real Time Clock");
  // delay(3000);
  // lcd.clear();
   // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(" Hi!  ");
  display.display();
}
 
void loop () {
  DateTime now = RTC.now();

  display.clearDisplay(); 
  display.setCursor(0, 0); 
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.println(); 
  //display.print(' ');
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  display.println();
  display.display(); 
 
  
  // lcd.setCursor(0, 0);
  // lcd.print("Date: ");
  // lcd.setCursor(0, 1);
  // lcd.print("Time: ");
  
  // lcd.setCursor(6, 0);
  // lcd.print(now.year(), DEC);
  // lcd.print(":");
  // lcd.print(now.month(), DEC);
  // lcd.print(":");
  // lcd.print(now.day(), DEC);
 
  // lcd.setCursor(6, 1);
  // lcd.print(now.hour(), DEC);
  // lcd.print(":");
  // lcd.print(now.minute(), DEC);
  // lcd.print(":");
  // lcd.print(now.second(), DEC); 
  // delay(1000);
  // lcd.clear();
}
