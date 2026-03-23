
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#include<Servo.h> 

Servo penServo; 




void setup() {
  lcd.begin(16, 2); 
  Serial.begin(9600); 
  penServo.attach(6); 
  
  lcd.home(); 
  lcd.println("Setup done:");
  penServo.write(0); 
}

void loop() {
 if(Serial.available() > 0)
 {
  char command = Serial.read(); 
  switch(command)
  {
    case 'u':
    {
      penServo.write(0); 
      lcd.home(); 
      lcd.print("Pen is up"); 
      delay(100); 
    }
    break; 
    case 'd':
    {
      penServo.write(40); 
      lcd.home(); 
      lcd.print("Pen is down"); 
      delay(100); 
    }
    break; 

    default:
    break; 
  }
 }

}
