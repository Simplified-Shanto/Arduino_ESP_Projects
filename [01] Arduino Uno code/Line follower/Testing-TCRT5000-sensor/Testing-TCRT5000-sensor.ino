
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define middleSensorReading analogRead(A3)


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    //for(;;); // Don't proceed, loop forever
  }

  delay(2000); // Pause for 2 seconds
  OLED.clearDisplay(); 
  OLED.setTextSize(1); 
  OLED.setTextColor(WHITE); 
  OLED.setCursor(0,0); 
  //DISPLAY static text
  OLED.println("HELLO, WORLD! :)"); 
  OLED.display(); 
  delay(1000); 
}

void loop() {
  OLED.clearDisplay(); 
  OLED.setCursor(0,0); 
  OLED.println(middleSensorReading); 
  OLED.display(); 
  Serial.println(middleSensorReading); 
  delay(200); 

}
