#include<Servo.h> 

Servo servoA ; 

void setup() {
 servoA.attach(D3, 500, 2400); 
 
 servoA.write(0); 
 delay(1000); 
 servoA.write(180);
 delay(1000); 

}

void loop() {
  for(int i = 0; i <= 180; i++){
    servoA.write(i); 
    delay(15); 
  }

  delay(1000); 

  for(int i = 180; i>=0; i-=30)
  {
    servoA.write(i); 
    delay(300); 
  }

  delay(1000); 
  

}
