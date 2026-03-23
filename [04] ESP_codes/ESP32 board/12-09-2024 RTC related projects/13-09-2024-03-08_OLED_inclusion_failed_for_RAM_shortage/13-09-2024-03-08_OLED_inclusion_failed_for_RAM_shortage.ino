/*
  DS3231: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/
/*
We tried to run this code on arduino nano, but it failed due to RAM 
shortage. 



*/



#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

void setup()
{
  

  Serial.begin(9600);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hi!");
  display.display();


  // Initialize DS3231
  //display.println("Initialize DS3231");;
  clock.begin();

  // Set sketch compiling time
  //clock.setDateTime(2024, 9, 12, 3, 34, 30);
  //clock.setDateTime(__DATE__, __TIME__);
  clock.dateFormat("D M d H:i:s",dt); 
}

void loop()
{
  dt = clock.getDateTime();

  // For leading zero look to DS3231_dateformat example

 // display.print("Raw data: ");
 display.clearDisplay(); 
 display.setCursor(0, 0); 
  display.print(dt.year);   display.print("-");
  display.print(dt.month);  display.print("-");
  display.print(dt.day);    display.print(" ");
  display.print(dt.hour);   display.print(":");
  display.print(dt.minute); display.print(":");
  display.print(dt.second); display.println("");

  display.display(); 


  delay(1000);
}
