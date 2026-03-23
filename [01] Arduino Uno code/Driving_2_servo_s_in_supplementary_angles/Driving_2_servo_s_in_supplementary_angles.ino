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
  delay(5000); 
  
}

  int Direction = 1; 

void loop() {
 if(Direction==1)
 {
  while(rightServoAngle>2)
  {
    rightServoAngle--; 
    leftServoAngle++; 
    leftServo.write(leftServoAngle); 
    rightServo.write(rightServoAngle); 
    delay(50); 
    lcd.setCursor(0,0); 
 lcd.print("Left"); 
 lcd.setCursor(0,1); 
 lcd.print(leftServoAngle); 
 lcd.setCursor(7, 0); 
 lcd.print("Right"); 
 lcd.setCursor(7, 1); 
 lcd.print(rightServoAngle); 
  }
  if(rightServoAngle==2)
  {
    Direction = -1; 
  }
 }
 else
 {
  while(leftServoAngle>2)
  {
    leftServoAngle--; 
    rightServoAngle++; 
     leftServo.write(leftServoAngle); 
    rightServo.write(rightServoAngle); 
    delay(50); 
    lcd.setCursor(0,0); 
 lcd.print("Left"); 
 lcd.setCursor(0,1); 
 lcd.print(leftServoAngle); 
 lcd.setCursor(7, 0); 
 lcd.print("Right"); 
 lcd.setCursor(7, 1); 
 lcd.print(rightServoAngle); 
  }
  if(leftServoAngle==2)
  {
    Direction = 1; 
  }
 }

 

 
}
