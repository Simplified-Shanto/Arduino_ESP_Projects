#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
#include<Servo.h> 
#include"stepMechanism.h"
/*
 *This version does following functions:  
 *
 *1. Can put the pen Up and Down with commands 'u' and 'd' respectively. 
 *2. Can initialize the position of the pen-carrier nearest to the motor via the horizontal switch. 
 *3. Can move the pen-carrier forward and backward direction with the commands 'f' and 'b' respectively. 
 *4. Can constrain the movement of the pencarrier up to it's range. When the carrier reaches end, 'f' 
 *    command will no longer move it further and the same applies for 'b'.
 *5. Shows the position of the pen-carrier in the format "x:X" where x is the current position and  
 *   X is the maximum position. 
 *6. In this version, functionalities are taken to separate header "stepMechanism.h"
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
Servo penServo; 
unsigned short currentX = 0; //The current position of the pen. 
#define maxXposition  28  //The maximum X position of the pen. 
#define minXposition 0    //Minimum X position of the pen. 

void setup() {
  lcd.init(); 
  lcd.backlight(); 
  Serial.begin(9600); 
  penServo.attach(6); 

  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(verticalSwitch, INPUT); 
  
  lcd.setCursor(0,0); 
  lcd.println("Setup done:");
  penServo.write(0); 
  delay(500); 

  
   boolean positionInitialized = false; 
    while(positionInitialized == false)
  {
    if(digitalRead(verticalSwitch)!=0)
    {
      positionInitialized = true; 
     lcd.setCursor(0,0); 
      lcd.print("Condition matched"); 
      delay(500); 
    }
    else
    {
      stepBackward(1, 10); 
    }
  }

  lcd.setCursor(0,0); 
  lcd.println("Pos initialized"); 
  delay(1000); 
  lcd.clear(); 
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
      delay(500); 
    }
    break; 
    case 'd':
    {
      penServo.write(40); 
      lcd.home(); 
      lcd.print("Pen is down"); 
      delay(500); 
    }
    break; 
    case 'b':
    {
      if(currentX > 0)
      {
      stepBackward(1, 10);
      if(currentX%10==0) { lcd.setCursor(2,0); lcd.print("            "); } //Clearing garbage value on the lcd. 
      currentX--; 
      }
    }
    break; 
    case 'f': 
    {
      if(currentX < maxXposition)
      {
      stepForward(1, 10); 
      if(currentX%10==0) { lcd.setCursor(2,0); lcd.print("            "); } //Clearing garbage value on the lcd. 
      currentX++; 
      }
    }

    default:
    break; 
  }
 }
  lcd.setCursor(0,0); 
  lcd.print("X: ");
  lcd.print(currentX); 
}
