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



void setup() {

  Wire.begin();  // Start the I2C
  RTC.begin();   // Init RTC

  //  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
  // display.print("Time and date set");
  // lcd.setCursor(0, 0);
  // lcd.print("Real Time Clock");
  // delay(3000);
  // lcd.clear();
  // Initialize OLED display
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

   checkEncoder(); 
  display.println(counter);
  display.display();
  checkEncoder(); 

  if(digitalRead(encoderButtonPin)==0)
  {
    //Serial.println("Button Pressed!"); 
    counter = 0; 
      delay(200);  //Debounce time. 
  }
}


void checkEncoder()
{
    // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);
  // If the previous and current state of the inputCLK are different
  // then a pulse has occurred

  if (currentStateCLK != previousStateCLK) {
    // If the inputDT state is different than the inputCLK state
    // then the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
    } else {
      // the encoder is rotating clockwise;
      counter++;
    }
    // Update previousStateCLK with the current state
  }
  previousStateCLK = currentStateCLK; 
}
