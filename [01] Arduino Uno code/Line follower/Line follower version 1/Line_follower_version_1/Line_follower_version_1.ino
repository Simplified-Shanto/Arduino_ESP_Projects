#define rightVal  analogRead(A1)    //Go right if the purple wire faces black. 
#define leftVal  analogRead(A3)

#define threshold 40

//Pin declaration for left motor. 
#define enL  3
#define in1  4
#define in2  2

//Pin declaration for right motor. 
#define enR  5
#define in3  7
#define in4  6


void setup() {
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
  pinMode(A4, INPUT); 

  pinMode(enL, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 

  pinMode(enR, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
    Serial.begin(9600); 

    for(int i = 1; i<=5; i++)
    {
      if(i%2==0)
      {
      digitalWrite(13, LOW); 
      }
      else
      {
        digitalWrite(13, HIGH); 
      }
      delay(1000); 
    }
}
#define PWM 100
#define wait 0

// red blue brown purple yellow orange green  

void loop() {
 /*
Serial.print(analogRead(A0)); 
Serial.print("   "); 
Serial.print(analogRead(A1)); 
Serial.print("   ");  
Serial.print(analogRead(A2)); 
Serial.print("   "); 
Serial.print(analogRead(A3)); 
Serial.print("   "); 
Serial.print(analogRead(A4));
Serial.print("\n"); 
 delay(500); 
*/
if(leftVal > 40 && rightVal > 40)
{
  goForward(80); 
  delay(wait); 
}
else if(leftVal < 40)
{
  goLeft(PWM); 
  delay(wait); 
}

else if(rightVal < 40)
{
  goRight(PWM);
  delay(wait); 
}



}

void Stop()
{
  digitalWrite(enL, LOW); 
  digitalWrite(enR, LOW); 
}

void rightForward(int actionValue) //Sets the right motor to move forward
{
  analogWrite(enR, actionValue); 
   digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
}

void rightBackward(int actionValue)
{
  analogWrite(enR, actionValue); 
   digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
}

void leftForward(int actionValue)
{
analogWrite(enL, actionValue); 
   digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  
}

void leftBackward(int actionValue)
{
  analogWrite(enL, actionValue); 
   digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
}


void goForward(int actionValue)
{
 rightForward(actionValue); 
 leftForward(actionValue); 
}

void goBackward(int actionValue)
{
  rightBackward(actionValue); 
  leftBackward(actionValue); 
}

void goLeft(int actionValue)
{
 rightForward(actionValue); 
 leftBackward(actionValue); 
}


void goRight(int actionValue)
{
    leftForward(actionValue); 
    rightBackward(actionValue); 
}
