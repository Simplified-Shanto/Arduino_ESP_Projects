#include<LiquidCrystal_I2C.h>
#include<Servo.h> 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


Servo leftServo; 
Servo rightServo; 
int leftServoAngle = 2;
int rightServoAngle = 178; 
int maxAngle = 178; //The maximum angle we'll rotate the servo motors
int minAngle = 2; //The minimum angle we'll rotate the servo motors

void setup() {
  lcd.begin(16, 2); 
  Serial.begin(9600); 
  leftServo.attach(9); 
  rightServo.attach(5); 
  lcd.home();
  lcd.print("Hi!"); 
  delay(700); 
  lcd.clear(); 
  leftServo.write(leftServoAngle); 
  rightServo.write(rightServoAngle); 
}

void loop() {

  if(Serial.available() > 0)
{
  char x = Serial.read(); 
  switch(x)
  {
    case '1':
    {
      leftServoAngle+=(leftServoAngle < maxAngle); 
    }
    break; 
    
    case '2':
    {
      leftServoAngle-=(leftServoAngle > minAngle); 
    }
    break; 
    
    case '3':
    {
      rightServoAngle+=(rightServoAngle < maxAngle); 
    }
    break; 
    
    case '4':
    {
      rightServoAngle-=(rightServoAngle > minAngle); 
    }
    break; 
    default:
    break; 
  }
  leftServo.write(leftServoAngle); 
  rightServo.write(rightServoAngle); 
  lcd.clear(); 
}

 lcd.setCursor(0,0); 
 lcd.print("Left"); 
 lcd.setCursor(0,1); 
 lcd.print(leftServoAngle); 
 lcd.setCursor(7, 0); 
 lcd.print("Right"); 
 lcd.setCursor(7, 1); 
 lcd.print(rightServoAngle); 

 
}
