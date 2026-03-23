
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

//Define LCD pinout. 
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3; 

//Define I2C address - change if required 
const int i2c_addr = 0x3F; 

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE); 

#define s1 D4
#define s2 D3



void setup() {
 lcd.begin(16, 2); 
 pinMode(A0, INPUT); 
 pinMode(s1, OUTPUT); 
 pinMode(s2, OUTPUT); 
 
 digitalWrite(D4,LOW); 
 digitalWrite(D3, LOW); 
}

int varX, varY; 

void loop() {
  digitalWrite(s1, LOW); 
  digitalWrite(s2, HIGH); 
  delay(10); 
 
  varX = analogRead(A0); 
  if(varX%10==0) { lcd.clear(); }
  lcd.setCursor(0, 0); 
  lcd.print("X = "); 
  lcd.setCursor(5 , 0);
  lcd.print(varX); 
  delay(10); 
 
 
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, LOW); 
  delay(10); 

  varY = analogRead(A0); 
  lcd.setCursor(0, 1); 
  lcd.print("Y = "); 
  lcd.setCursor(5, 1);
  lcd.print(varY); 
      delay(10); 
 
delay(100); 
  
 
}
