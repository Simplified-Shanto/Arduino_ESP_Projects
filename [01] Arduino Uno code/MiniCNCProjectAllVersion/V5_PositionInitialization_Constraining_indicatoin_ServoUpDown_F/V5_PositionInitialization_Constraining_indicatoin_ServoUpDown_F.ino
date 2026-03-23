#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
#include<Servo.h> 
/*
 *This version does following functions:  
 *
 *1. Can put the pen Up and Down with commands 'u' and 'd' respectively. 
 *2. Can initialize the position of the pen-carrier nearest to the motor via the horizontal switch. 
 *3. Can move the pen-carrier forward and backward direction with the commands 'f' and 'b' respectively. 
 *4. Can constrain the movement of the pencarrier up to it's range. When the carrier reaches end, 'f' 
 *    command will no longer move it further and the same applies for 'b'.
 *5. Shows the position of the pen-carrier in the format "x:X" where x is the current positioni and  
 *   X is the maximum position. 
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

#define in1 2 //A+ 
#define in2 3 //A-
#define in3 4 //B+
#define in4 5 //B-
#define verticalSwitch 9

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

#define highTime 2   //The period of phase being turned on in millisecond. 

void stepBackward(int stepCount, int switchGap)  //function for one backward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  
  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------

  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 

   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
 }
}

void stepForward(int stepCount, int switchGap)  //Function for one forward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------
  
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
 delay(switchGap); 


   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 

  
  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  
 }
 
 
}
