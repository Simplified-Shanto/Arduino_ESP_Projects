// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(3);

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps
                       // Serial.println("Motor test!");

  // turn on motor
  leftMotor.setSpeed(150);
  rightMotor.setSpeed(150);

  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

#define runTime 500
#define leftRightSpeed 80
unsigned long timer;
byte speed = 0; 


void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    timer = millis();
    float speedVal = command - '0';
    if (speedVal >= 0 and speedVal <= 10) {
      speedVal = floor((speedVal / 10) * 255.00);
      speed = int(speedVal); 
      //Serial.println(speed); 
      leftMotor.setSpeed(speed);
      rightMotor.setSpeed(speed);
    } else {
      switch (command) {
        case 'F':
          {
            leftMotor.setSpeed(speed); 
            rightMotor.setSpeed(speed); 
            leftMotor.run(FORWARD);
            rightMotor.run(FORWARD);
          }
          break;
        case 'B':
          {
            leftMotor.setSpeed(speed); 
            rightMotor.setSpeed(speed); 
            rightMotor.run(BACKWARD);
            leftMotor.run(BACKWARD);
          }
          break;
        case 'L':
          {
            rightMotor.setSpeed(leftRightSpeed); 
            leftMotor.setSpeed(leftRightSpeed); 
            rightMotor.run(FORWARD);
            leftMotor.run(BACKWARD);
          }
          break;
        case 'R':
          {
            rightMotor.setSpeed(leftRightSpeed); 
            leftMotor.setSpeed(leftRightSpeed); 
            rightMotor.run(BACKWARD);
            leftMotor.run(FORWARD);
          }
        default:
          break;
      }
    }
  }


  if (millis() - timer > runTime) {
    rightMotor.run(RELEASE);
    leftMotor.run(RELEASE);
  }


}
