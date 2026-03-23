/*22-7-2023
 * Nayeem Islam Shanto
 * Contact: islamshafiul283@gmail.com
 * 
 * This piece of codes drives a stepper motor without using the Stepper library. 
 * Here, we generate the step sequences for forward and backward stepping of the stepper motor. 
 * The code was tested with a CD-DRIVE stepper motor and L293D motor driver. 
 * 
 */

#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#include<Servo.h> 
#include "Stepmechanism.h"


#define penServoPin 9
Servo penServo; 

void penUp()
{
  penServo.write(40); 
  
}
void penDown()
{
  penServo.write(0); 

}



void setup() {
  Serial.begin(9600); 
  lcd.begin(16,2); 
  lcd.print("Hi!"); 
  penServo.attach(penServoPin); 
  delay(700); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);
  
  pinMode(In1, OUTPUT); 
  pinMode(In2, OUTPUT); 
  pinMode(In3, OUTPUT); 
  pinMode(In4, OUTPUT);
  pinMode(horizontalSwitchPin, INPUT); 
  pinMode(verticalSwitchPin, INPUT); 

  penUp(); 
  //initializePosition(); 
}



int counter  = 0; 


void loop()
{
  lcd.setCursor(0,1);   //Just a counter is run on the lcd display. 
  counter = millis()/10000; 
  lcd.print(counter); 
  if(Serial.available() > 0)
  {
    char command = Serial.read(); 
    if(command=='f')
    {
      HstepForward(1, 10); //First parameter indicates the number of steps, second parameter indicates 
    }                     //the speed (the delay between switchings the phases of the motor)
    else if(command == 'b')
    {
      HstepBackward(1, 10); 
    }
    else if(command == 'r')
    {
      VstepBackward(1, 10); 
    }
    else if(command == 'l')
    {
      VstepForward(1, 10); 
    }
    else if(command == 'u')
    {
      penServo.write(40); 
      Serial.println("Command = u"); 
    }
    else if(command == 'd'); 
    {
      penServo.write(2); 
      Serial.println("Command = d"); 
    }
  }
}
