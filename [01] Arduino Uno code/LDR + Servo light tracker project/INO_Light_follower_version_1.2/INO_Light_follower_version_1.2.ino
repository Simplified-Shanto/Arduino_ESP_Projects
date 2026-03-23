#include<Servo.h>

Servo servoX;  //The X axis servo 
Servo servoY;  //The y axis servo

//The LDRs are named according to the quadrant names 
//of conventional coordinate system. 

//Servo pins
#define servoXpin  9   //Digital pin 9
#define servoYpin  5   //Digital pin 5

void setup() {
    Serial.begin(9600); 
    servoX.attach(servoXpin); 
    servoY.attach(servoYpin);

    pinMode(A1, INPUT); 
    pinMode(A2, INPUT); 
    pinMode(A3, INPUT); 
    pinMode(A4, INPUT); 

    servoX.write(90); 
    servoY.write(90); 

    delay(1000); 

}

int xAngle = 90; 
int yAngle = 90; 
int difference = 50; 
int wait = 2; 
int change = 1; 

int ldr1, ldr2, ldr3, ldr4; 
void loop() {  
  //The values read from the LDRs are printed in Serial 
  // monitor in the form LDR1,LDR2.LDR3-LDR4
  ldr1  = analogRead(A1) ; 
 ldr2 =  analogRead(A2) ;
 ldr3  = analogRead(A3) ;
 ldr4  = analogRead(A4);
  
  Serial.print(ldr1); 
  Serial.print(','); 
  Serial.print(ldr2); 
  Serial.print('.'); 
  Serial.print(ldr3); 
  Serial.print('-'); 
  Serial.print(ldr4); 
  Serial.print('\n'); 
 
//This version of the conditions check whether both of the ldrs supports to change servo position. 

  if((ldr1 - ldr4 >= difference || ldr2 - ldr3 >= difference) &&  yAngle >= 20 )
  {
    yAngle-=change; 
    servoY.write(yAngle); 
    delay(wait); 
  }
  else if((ldr4 - ldr1 >= difference || ldr3 - ldr2 >= difference) &&   yAngle <=155) 
  {
    

    yAngle+=change; 
    servoY.write(yAngle); 
    delay(wait); 
  }

  if((ldr1 - ldr2 >= difference || ldr4 - ldr3 >= difference) && xAngle <= 160)
  {
    xAngle+=change; 
    servoX.write(xAngle); 
    delay(wait); 
  }
  else if((ldr2 - ldr1 >= difference || ldr3 - ldr4 >= difference) &&  xAngle >= 20  )
  {
    

     xAngle-=change; 
    servoX.write(xAngle); 
    delay(wait);
  }

   

  
}
