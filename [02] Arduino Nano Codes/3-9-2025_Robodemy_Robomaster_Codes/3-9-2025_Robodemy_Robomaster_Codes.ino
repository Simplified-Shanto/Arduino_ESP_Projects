#include<Adafruit_SSD1306.h> 
#include "bitmap.h"; 
#define frameCount  (sizeof(frames)/sizeof(frames[0])) 

Adafruit_SSD1306 display(128, 64, &Wire, -1); 
//128 = number of columns 
//64 = number of rows 
//&Wire = indicates to use I2C as communication medium. 
//-1 = means the display doesn't have a built in reset pin




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  if(!display.begin(0x02, 0x3C))
  {
    Serial.println("Display isn't initialized properly!"); 
  }
  display.begin(0x02, 0x3C);
  display.clearDisplay();  
  display.setTextSize(2); 
  display.setTextColor(1); 

  display.setCursor(0, 0); 
  display.println("Hi!"); 
  display.display(); 
  delay(1000); 
}

void loop() {
 for(int i = 0; i< frameCount; i++)
 {
  display.clearDisplay(); 
  display.drawBitmap(0, 0, frames[i], 64, 64, 1); 
  display.display(); 
 }
 delay(50); 
}
