
#include<AFMotor.h>
#include <Servo.h>

AF_DCMotor gearMotor(1); 
Servo myservo;  // create servo object to control a servo
Servo yourservo; 
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  yourservo.attach(10); 
}

void loop() {
  gearMotor.setSpeed(200); 
  gearMotor.run(FORWARD); 
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    yourservo.write(pos); 
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  gearMotor.run(RELEASE); 
  delay(1000); 
  gearMotor.run(BACKWARD); 
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    yourservo.write(pos); 
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

  gearMotor.run(RELEASE); 
  delay(1000); 

}
