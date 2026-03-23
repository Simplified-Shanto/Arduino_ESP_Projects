//Board: Esp8266
//Objective: To get to know the useful functionalities of OLED display. 
//To implement a simple counter on the oled. 
#include <iostream> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

#define SCREEN_WIDTH  128 //OLED display width, in pixels. 
#define SCREEN_HEIGHT 64  //OLED display height, in pixels. 

//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

int Seconds = 0; 
long lastMillis = millis(); 

void setup()
{
  Serial.begin(9600); 
  if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) //Address of our 128x64 display is 0x3C
  {
    Serial.println(F("SSD1306 allocation failed"));  //By wrapping the output string inside F() we store the string in the program flash memory instread of SRAM. 
    for(;;); //Keep looping forever. 
  }

  delay(2000); //waiting for the display to set up itself 

  OLED.clearDisplay(); 

  OLED.setTextSize(1); 
  OLED.setTextColor(WHITE); 
  OLED.setCursor(0,0); 
  //DISPLAY static text
  OLED.println("HELLO, WORLD! :)"); 
  OLED.display(); 
  delay(3000); 

  //OLED.clearDisplay(); 

  OLED.setTextSize(2); 
  OLED.setTextColor(WHITE); 
  OLED.setCursor(10,10); 

  OLED.println("Hi! Bangladesh"); 
  OLED.display(); 
  delay(3000); 
  OLED.clearDisplay(); 
  OLED.setCursor(0,0); 
}

String command = "nothingYet";
char commandType = 'b'; 
String commandValueString; 
int commandValue = 0; 
int millisDividend = 1000; 
int setCursorX = 0; 
int setCursorY = 0; 
//Command format: 'x:y.' where x is the type of command and y is the value.  
//s:x.    -> means set fontsize to x. 
//d:x.    -> set the millis() dividend to x. 
//c:x.    -> column value of setCursor()
//r:x.    -> row value of setCursor()
void loop()
{
  if(Serial.available())
  {
    
    command = Serial.readStringUntil('.'); 
    commandType = command[0];
    commandValueString = command.substring(2, command.length());  
    commandValue = commandValueString.toInt(); 
    std::cout << "commandType = " << commandType << " Value = " << commandValue << '\n'; 
    switch(commandType)
    {
      case 's': 
      {
        OLED.setTextSize(commandValue); 
      }
      break; 

      case 'd': 
      {
        millisDividend = commandValue; 
      }
      break; 
      case 'c':
      {
        setCursorX = commandValue; 
      }
      break; 
      case 'r':
      {
        setCursorY = commandValue; 
      }

      default: 
      break; 
    }
  }
  
  OLED.setCursor(setCursorX, setCursorY); 
  OLED.println(millis()/millisDividend); 
  OLED.display(); 
  OLED.clearDisplay(); 
}