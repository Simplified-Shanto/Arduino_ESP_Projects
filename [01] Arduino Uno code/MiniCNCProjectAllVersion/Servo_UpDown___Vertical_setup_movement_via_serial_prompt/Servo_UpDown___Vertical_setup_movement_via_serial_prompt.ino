
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#include<Servo.h> 
/*
 * I find serious bug in the step mechanism, 
 * which might causing the power-cut issue. 
 * I think there's shouldn't be any delay 
 * between Turning on and turning off a phase. 
 * 
 * *You might be interested to know how much time it takes 
 * to turn on and turn off a phase, by using 
 * millis() timestamps. 
 * 
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



void setup() {
  lcd.begin(16, 2); 
  Serial.begin(9600); 
  penServo.attach(6); 

  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  
  lcd.home(); 
  lcd.println("Setup done:");
  penServo.write(0); 
  delay(500); 
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
      stepBackward(1, 10); 
    }
    break; 
    case 'f': 
    {
      stepForward(1, 10); 
    }

    default:
    break; 
  }
 }

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
