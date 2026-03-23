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
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


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
 // Serial.begin(9600);


     if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
   xServo.attach(3); 
   yServo.attach(5); 
   xServo.write(90); 
   yServo.write(90); 
}





void loop() {
  xVal = analogRead(vrX); 
  yVal = analogRead(vrY); 


  // xVelocity = (xVal - 520.0)/scaleAngle; 
  // yVelocity = (yVal - 500.0)/scaleAngle; 

  // horAngle+=xVelocity; 
  // verAngle+=yVelocity; 

  // horAngle = constrain(horAngle, 2, 178); //Limiting the angles from 2 to 178 degrees. 
  // verAngle = constrain(verAngle, 2, 178); 

  if(horAngle<178 && xVal > 400)
  {
    horAngle++; 
    xServo.write(horAngle); 
    delay(10); 
  //  updateDisplay(); 
  }

  if(horAngle>0 && xVal < 200)
  {
    horAngle--; 
    xServo.write(horAngle); 
  //  updateDisplay(); 
  delay(10); 
  }

  if(verAngle<178 && yVal > 400)
  {
    verAngle++; 
    yServo.write(verAngle); 
  //  updateDisplay();
  delay(10);
  }

  if(verAngle>0 && yVal < 200)
  {
    verAngle--; 
    yServo.write(verAngle); 
    delay(10); 
   // updateDisplay();
  }



  

    
  
   if(millis() - lastSent > 500)   //Printing coordianates in x,y\n format to the Serial monitor. 
   {
      updateDisplay(); 
    lastSent = millis(); //Recording the last printing time. 
   }
        
 
   
 
 }


 void updateDisplay()
 {
  display.clearDisplay(); 
  display.setCursor(0, 0);
  display.print("varX  = ");
  display.println(xVal);
  display.print("yVal  = ");
  display.println(yVal);
  display.print("Servo 1 = ");
  display.println(horAngle);
  display.print("Servo 2 =  ");
  display.println(verAngle);
  display.display();
   
 }
