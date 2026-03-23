#include<Servo.h> 
//The six servos we'll include in our sketch will be named as a, b, c, d, e and f
//Serial command will be sent in the format "x:angle." -> here x is the name of the 
//servo motor (a, b, c, d, e or f) and x angle is the angle of the servo (0 <= angle <=180)

Servo aServo; 
Servo bServo; 
Servo cServo; 
Servo dServo; 
Servo eServo; 
Servo fServo; 


void setup() {
  Serial.begin(9600); 
  aServo.attach(D0, 500, 2400);
  bServo.attach(D1, 500, 2400); 
  cServo.attach(D3, 500, 2400); 
  dServo.attach(D4, 500, 2400); 
  eServo.attach(D5, 500, 2400); 
  fServo.attach(D6, 500, 2400); 
  
aServo.write(180); 
delay(2000); 
aServo.write(0); 
delay(2000); 

bServo.write(180); 
delay(2000); 
bServo.write(0); 
delay(2000); 

cServo.write(180); 
delay(2000); 
cServo.write(0); 
delay(2000); 

dServo.write(180); 
delay(2000); 
dServo.write(0); 
delay(2000); 

eServo.write(180); 
delay(2000); 
eServo.write(0); 
delay(2000); 

fServo.write(180); 
delay(2000); 
fServo.write(0); 
delay(2000); 
  

}
String command; 
char servoIndex; 
String servoAngle; 
byte angleValue ; 

void loop() {
  if(Serial.available())
  {
    command = Serial.readStringUntil('.'); 
    servoIndex = command[0]; 
    servoAngle = command.substring(2, command.length()); 
    angleValue = servoAngle.toInt(); 

    switch(servoIndex)
    {
      case 'a': 
      {
      aServo.write(angleValue); 
      } break; 
   
      
      case 'b':
      { 
      bServo.write(angleValue); 
      } break; 
      
      
      case 'c': 
      {
      cServo.write(angleValue); 
      } break;
     
      
      case 'd': 
      {
      dServo.write(angleValue); 
      } break; 
      
      case 'e': 
      {
      eServo.write(angleValue); 
      } break ; 

      
      
      case 'f': 
      {
      fServo.write(angleValue);
      } break; 
      
      default: 
      break; 
    }
    delay(10); 
  }

}
