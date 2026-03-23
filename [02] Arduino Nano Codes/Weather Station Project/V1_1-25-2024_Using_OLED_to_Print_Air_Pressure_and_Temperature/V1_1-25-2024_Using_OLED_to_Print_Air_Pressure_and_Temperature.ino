// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
//#include <MQUnifiedsensor.h>
//#include <string.h>


#define SCREEN_WIDTH  128 //OLED display width, in pixels. 
#define SCREEN_HEIGHT 64  //OLED display height, in pixels. 

//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  bmp.begin(); 
      /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) //Address of our 128x64 display is 0x3C
  {
    Serial.println(F("SSD1306 allocation failed"));  //By wrapping the output string inside F() we store the string in the program flash memory instread of SRAM. 
   // for(;;); //Keep looping forever. 
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

}

byte lastRead = millis()/1000; 
void loop() {
  // put your main code here, to run repeatedly:
    if(millis()/1000 - lastRead > 3)
    {
      lastRead = millis()/1000; 
     

      OLED.clearDisplay(); 
      OLED.setCursor(0, 0); 
      OLED.println(bmp.readTemperature()); 

      OLED.setCursor(0,10); 
      OLED.println(bmp.readPressure()); 
      OLED.display(); 


      Serial.print("Temperature: "); 
      Serial.println(bmp.readTemperature()); 
      Serial.print("Air pressure: "); 
      Serial.println(bmp.readPressure()); 

    }
}
