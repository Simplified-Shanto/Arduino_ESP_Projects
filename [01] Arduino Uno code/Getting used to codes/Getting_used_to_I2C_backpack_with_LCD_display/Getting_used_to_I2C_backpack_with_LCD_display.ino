
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

//Define LCD pinout. 

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3; 

//Define I2C address - change if required 
const int i2c_addr = 0x3F; 

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE); 


void setup() {
 // put your setup code here, to run once:
 lcd.begin(16, 2); 

 lcd.setCursor(0, 0); 
 lcd.print("Hello world!"); 

 delay(1000); 

 lcd.setCursor(0,1);
 lcd.print("How are you?"); 
 
 delay(3000); 

 lcd.clear(); 

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0); 
  lcd.print("Backlight demo"); 
  lcd.setCursor(0,1); 
  lcd.print("Flash 4 times"); 

  delay(3000); 
  lcd.clear(); 

  //Flash backlight 4 times 
  for(int i = 0; i<4; i++)
  {
    lcd.backlight(); 
    delay(250); 
    lcd.noBacklight(); 
    delay(250);
  }

  lcd.backlight(); 
delay(1000); 
}
