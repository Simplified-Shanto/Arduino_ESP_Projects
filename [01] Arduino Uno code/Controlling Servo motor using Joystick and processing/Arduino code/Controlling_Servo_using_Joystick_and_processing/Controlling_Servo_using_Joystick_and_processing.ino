/*
 * Last Modified: 29-10-2022
 * Author: Nayeem Islam Shanto (islamnayeem386@gmail.com)
 * 
 * This code drives 2 SG90 servo motor connected to Arduino via a 2 axis joystick. 
 * Besides, it prints the reading of the Joystick coordinates to the Serial Monitor. 
 * Which can be used in Serial Communication via processing. 
 */




/*
 *Used pins:  
 *A0 - X axis value of the Joystick. 
 *A1 - Y axis value of the Joystick. 
 *~9 - PWM pin of horizontal servo
 *~10 - PWM pin of Vertical servo. 
 */

#include<Servo.h>

Servo xServo;     
Servo yServo; 

const int vrX = A0; 
const int vrY = A1; 
const int stickButton = 2; 


int xVal = 0; 
int yVal = 0; 

float horAngle = 90;
float verAngle = 90;
float xVelocity = 0; 
float yVelocity = 0; 

float scaleAngle = 450.00;   //Scale down the reading from Joystick to a convenient angular velocity. 


long long int lastSent = millis(); //Variable to store last time the X and Y value of the joystick was printed to the Serial monitor. 

void setup() {
  pinMode(vrX, INPUT); 
  pinMode(vrY, INPUT); 
  Serial.begin(9600);

   xServo.attach(10); 
   yServo.attach(9); 
}





void loop() {
  xVal = analogRead(vrX); 
  yVal = analogRead(vrY); 


  xVelocity = (xVal - 520.0)/scaleAngle; 
  yVelocity = (yVal - 500.0)/scaleAngle; 

  horAngle+=xVelocity; 
  verAngle+=yVelocity; 

  horAngle = constrain(horAngle, 2, 178); //Limiting the angles from 2 to 178 degrees. 
  verAngle = constrain(verAngle, 2, 178); 
  
    xServo.write(horAngle); 
    yServo.write(verAngle); 
    

   
  //  if(millis() - lastSent > 200)   //Printing coordianates in x,y\n format to the Serial monitor. 
  //  {
  //      Serial.print(xVal); 
  //   Serial.print(','); 
  //   Serial.print(yVal); 
  //   Serial.print('\n'); 
  //   lastSent = millis(); //Recording the last printing time. 
  //  }
        
  
     delay(5); 
 
 }
