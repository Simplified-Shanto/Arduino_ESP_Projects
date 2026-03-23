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

#define in1 2 //A+ 
#define in2 3 //A-
#define in3 4 //B+
#define in4 5 //B-



void stepBackward(int stepCount, int switchGap)  //function for one backward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 

  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------

  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 

   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(switchGap); 
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
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------
  
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 



   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 

  
  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  
 }
 
 
}


void setup() {
  Serial.begin(9600); 
  lcd.begin(16,2); 
  lcd.print("Hi!"); 
  delay(700); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);

    digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 

  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 

}

int counter  = 0; 
void loop() {
  lcd.setCursor(0,1);   //Just a counter is run on the lcd display. 
  counter = millis()/10000; 
  lcd.print(counter); 
  if(Serial.available() > 0)
  {
    char command = Serial.read(); 
    if(command=='f')
    {
      stepForward(5, 10); //First parameter indicates the number of steps, second parameter indicates 
    }                     //the speed (the delay between switchings the phases of the motor)
    else if(command == 'b')
    {
      stepBackward(5, 10); 
    }
  }

}
