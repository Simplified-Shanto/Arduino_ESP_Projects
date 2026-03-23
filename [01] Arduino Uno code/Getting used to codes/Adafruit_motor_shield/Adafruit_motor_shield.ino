#include<AFMotor.h>
#include<Servo.h> 


//2 servo motor pins are hooked up at pin 9 and pin 10. 

//Challenge: 
/*
 * 1 gear motor and 2 motorized wheel has been connected with the shield. 
 * Along with it there are 2 servo motors. 
 * 
 * All the motors will rotate forward at 200 speed for 3 second, stop for 2 second, rotate backward for 3 second and the process repeats. 
 * Simultaneously the servo motors will go left to right and up to down simultaneously. 
 */

AF_DCMotor gearMotor(3);
AF_DCMotor leftWheel(1); 
AF_DCMotor rightWheel(2);  

Servo servoX; 
Servo servoY; 

long long lastCalc = millis(); 
byte state = 0; //Whether the motor is running or not. 
int motorRun = 3000;    //Runtime of the motors.
int motorPause = 2000;  //The pause period for the motors. 
int servoChange = 1;    //Angle that is chaged at a time. 
int servoDelay = 9;     //Delay between two subsequent writings. 
int servoMin = 10;       //Max writing angle 
int servoMax = 170;      //Mininmum writing angle. 
byte xAngle = 90; 
byte yAngle = 90; 
byte flag = 1; 

//Let's create 4 state - 0 (for) , 1(stop) , 2(back), 3(stop); 

void setup()
{
  servoX.attach(9); 
  servoY.attach(10); 
  servoX.write(90); 
  servoY.write(90);

   gearMotor.setSpeed(200); 
    leftWheel.setSpeed(200); 
    rightWheel.setSpeed(200); 
}

void loop()
{
  if(state%2==0 && millis() - lastCalc >= motorPause)
  {
     if(state==0)
     {
     gearMotor.run(FORWARD); 
    leftWheel.run(FORWARD); 
    rightWheel.run(FORWARD); 
    
      state = 1; 
     }
     else if(state==2)
     {
       gearMotor.run(BACKWARD); 
    leftWheel.run(BACKWARD); 
    rightWheel.run(BACKWARD); 

      state = 3; 
     }
     
      
    lastCalc = millis(); 
  }

  if(state%2==1 && millis() - lastCalc >= motorRun)
  {
    gearMotor.run(RELEASE); 
    leftWheel.run(RELEASE); 
    rightWheel.run(RELEASE); 

    state++; 
    state%=4; 

    lastCalc = millis(); 
  }


  if(flag==1)
  {
    xAngle++;
    yAngle++; 
    if(xAngle>=servoMax)
    {
      flag = 0; 
    }
  }

  if(flag = 0)
  {
    yAngle--; 
    xAngle--; 
    if(xAngle<=servoMin)
    {
      flag = 1; 
    }
  }

  servoX.write(xAngle); 
  servoY.write(yAngle);  
  
}
