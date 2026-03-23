#include<Servo.h> 

Servo servoA ; 

void setup() {
 servoA.attach(D3, 500, 2400); 
 
 //servoA.write(0); 
// delay(1000); 
// servoA.write(180);
// delay(1000); 

}

void loop() {
 servoA.write(45); // rotate the motor counterclockwise

  delay(3000); // keep rotating for 5 seconds (5000 milliseconds)

  servoA.write(90); // stop the motor

  delay(3000); // stay stopped

  servoA.write(135); // rotate the motor clockwise

  delay(3000); // keep rotating :D

}
