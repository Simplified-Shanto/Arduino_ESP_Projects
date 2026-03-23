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
 *   ----------------------------------------------------------------------------------------------
 *   V7 updates 8/8/2023
 *   ----------------------------------------------------------------------------------------------
 *6. In this version, functionalities are taken to separate header "stepMechanism.h"
 *7. Addition of the horizontal setup movement mechanism with command 'l' for left and 'r' for right. 
 *8. Initialization mechanism for the horizontal setup. 
 *9. Adding constraint for the range of horizontal setup with the variable Y
 *10.Displaying the current Y position on the LCD display with variable current Y
 *   ----------------------------------------------------------------------------------------------
 *   V8 updates 8/8/2023
 *   ----------------------------------------------------------------------------------------------
 *11. Adding a drawGraph function to draw graph. 
 *   ----------------------------------------------------------------------------------------------
 *   V9 updates 9/8/2023
 *   ----------------------------------------------------------------------------------------------
 *12. Adding the stepping range constraining mechanism inside stepLeft, stepForward inside functions
 *    instead of checking range before calling stepLeft(), stepForward etc. 
 *13. Updating the currentX and currentY variables inside the stepLeft(), stepForward() functions 
 *    instead of updating manually. 
 *    10/8/2023
 *14. Fixed some logical error inside stepMechanism + fine tuned display output. 
 *15. Found out the correct range of the horizontal and vertical setup. 
 *16. Included penUp() and penDown() functions instead of writing particular angle to the 
 *    pan carrier servo motor. 
 *    
 *    
 *   
 *   
 *   ------------------------------------------------------------------------------------------------
 * Handy Arduino IDE shortcuts:  
 * Upload code          - Ctrl + U
 * Compile sketch       - Ctrl + R 
 * Serial monitor       - Ctrl + Shift + M 
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
int switchGap = 5;  //The time between switching two phases

void setup() {
  penServo.attach(6); 
  penUp(); 
  lcd.init(); 
  lcd.backlight(); 
  Serial.begin(9600); 
  

  //Pinmode declaration for vertical setup
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  //Pinmode declaration for horizontal setup
  pinMode(In1, OUTPUT); 
  pinMode(In2, OUTPUT); 
  pinMode(In3, OUTPUT); 
  pinMode(In4, OUTPUT); 
  
  pinMode(verticalSwitch, INPUT); 
  pinMode(horizontalSwitch, INPUT); 

  
  
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

     positionInitialized = false; 
    while(positionInitialized == false)
  {
    if(digitalRead(horizontalSwitch)!=0)
    {
      positionInitialized = true; 
     lcd.setCursor(0,0); 
      lcd.print("Condition matched"); 
      delay(500); 
    }
    else
    {
      stepRight(1, 10); 
    }
  }

  currentX = 0; 
  currentY = 0; 
  

  lcd.setCursor(0,0); 
  lcd.println("Pos initialized"); 
  delay(1000); 
  lcd.clear(); 



  delay(1000); 
  drawGraph(); 
  delay(1000); 

  lcd.setCursor(0,0); 
  lcd.println("Setup done:");
  delay(500); 
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
      //penServo.write(0); 
      penUp(); 
      lcd.setCursor(7, 0); 
      lcd.print("     "); 
      lcd.setCursor(7,0); 
      lcd.print("penUp"); 
      delay(500); 
    }
    break; 
    case 'd':
    {
     // penServo.write(40); 
     penDown(); 
      lcd.setCursor(7, 0); 
      lcd.print("       "); 
      lcd.setCursor(7,0); 
      lcd.print("penDown"); 
      delay(500); 
    }
    break; 
    case 'b':
    {
      stepBackward(1, switchGap);
      if(currentX%9==0) { lcd.setCursor(2,0); lcd.print("            "); } //Clearing garbage value on the lcd. 
    }
    break; 
    case 'f': 
    {
      stepForward(1, switchGap); 
      if(currentX%9==0) { lcd.setCursor(2,0); lcd.print("            "); } //Clearing garbage value on the lcd. 
    }
    break;
    case 'r':
    {
      stepRight(1, switchGap);
      if(currentY%9==0) { lcd.setCursor(2,1); lcd.print("            "); } //Clearing garbage value on the lcd. 
    }
    break; 
    case 'l': 
    {
      stepLeft(1, switchGap); 
      if(currentY%9==0) { lcd.setCursor(2,1); lcd.print("            "); } //Clearing garbage value on the lcd. 
    }
    break;

    default:
    break; 
  }
 }
  lcd.setCursor(0,0); 
  lcd.print("X: ");
  lcd.print(currentX); 
  lcd.setCursor(0,1); 
  lcd.print("Y: "); 
  lcd.print(currentY); 
}

#define printTime 5

void drawGraph()    //Function to draw a graph paper. 
 {
   
  for(int i = 1; i<=7; i++)
  {
    penDown();  
    
    stepForward(50,printTime); 
    
    penUp();  
    
    delay(500); 
    
    stepLeft(5,printTime); 
    
    delay(500);
     
    penDown(); 
    
    stepBackward(50,printTime);
    
    penUp(); 
    
    delay(500); 
    
    stepLeft(5,printTime);  
    
    delay(500); 

    lcd.setCursor(0,0); 
  lcd.print("X: ");
  lcd.print(currentX); 
  lcd.setCursor(0,1); 
  lcd.print("Y: "); 
  lcd.print(currentY); 
  }


  for(int i = 1; i<=6; i++)
  {
    penDown();  
    
    stepRight(65,printTime); 
    
    penUp(); 
    
    delay(500); 
    
    stepForward(5,printTime); 
    
    delay(500); 
    
    penDown();
      
    stepLeft(65,printTime);
    
    penUp(); 
    
    delay(500); 
    
    stepForward(5,printTime); 
     
    delay(500); 

    lcd.setCursor(0,0); 
  lcd.print("X: ");
  lcd.print(currentX); 
  lcd.setCursor(0,1); 
  lcd.print("Y: "); 
  lcd.print(currentY); 
  }
 }


 void penUp()
{
   penServo.write(0); 
   delay(200); 
}
void penDown()
{
  penServo.write(40); 
  delay(200); 
}
