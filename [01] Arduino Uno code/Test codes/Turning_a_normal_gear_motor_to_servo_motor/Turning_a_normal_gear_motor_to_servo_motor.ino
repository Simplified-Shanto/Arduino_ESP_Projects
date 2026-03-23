#include<Servo.h> 
#define servoPin 3
Servo gearServo; 

void setup() {
  Serial.begin(9600); 
  gearServo.attach(servoPin); 
  gearServo.write(90); 

}


void loop() {
 if(Serial.available())
 {
  String command = Serial.readStringUntil("."); 
  command = command.substring(0, command.length()); 
  int angle = command.toInt(); 
  gearServo.write(angle); 
 }

}
