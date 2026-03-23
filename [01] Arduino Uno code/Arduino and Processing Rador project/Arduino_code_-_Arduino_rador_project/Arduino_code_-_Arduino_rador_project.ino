/*Project started: 01-11-2022
 * 
 * 
 * 
 */
 #include<Servo.h>

 Servo xServo; 
 const int xServoPin = 9; 
 const int trigPin = 10; 
 const int echoPin  = 11; 
 

 long duration; 
 int distance; 

 int timeGap =  5; 

void setup() {
    xServo.attach(xServoPin); 
    pinMode(echoPin, INPUT); 
    pinMode(trigPin, OUTPUT); 

    Serial.begin(9600); 
}
long Dis; 

void loop() {

  //Runs the servo from 15 to 165 degree, calculates distance and prints it to the Serial Monitor. 
for(int i = 0; i<=180; i++)
{
  xServo.write(i); 
  delay(timeGap); 
  Dis= calculateDistance(); 

  Serial.print(i); 
  Serial.print(','); 
  Serial.print(Dis); 
  Serial.print('.'); 
}


  //Runs the servo from 165 to 15 degree, calculates distance and prints it to the Serial Monitor. 
for(int i = 180; i>=0; i--)
{
  xServo.write(i); 
  delay(timeGap); 
 Dis = calculateDistance(); 

  Serial.print(i); 
  Serial.print(','); 
  Serial.print(Dis); 
  Serial.print('.'); 
}
}


int calculateDistance()
{
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 

duration = pulseIn(echoPin, HIGH); 
distance = (duration*0.034)/2;  //Returns the distance in millimeter. 

return distance; 
}
