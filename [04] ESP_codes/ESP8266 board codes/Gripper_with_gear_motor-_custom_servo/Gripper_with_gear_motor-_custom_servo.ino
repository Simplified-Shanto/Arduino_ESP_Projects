#define in1 D1
#define in2 D2
#define plusButton D3
#define minusButton D4
#define potPin A0

void setup() {
 Serial.begin(9600); 
 pinMode(in1, OUTPUT); 
 pinMode(in2, OUTPUT); 
 pinMode(plusButton, INPUT); 
 pinMode(minusButton, INPUT); 
 pinMode(potPin, INPUT); 

}

void loop() {
  if(digitalRead(minusButton)!=0)
  {
    decreaseAngle(); 
    delay(10);
    doNotMove();  
  }
  else if(digitalRead(plusButton)!=0)
  {
    increaseAngle(); 
    delay(10); 
    doNotMove(); 
  }
  else
  {
    doNotMove(); 
  }

  Serial.println(analogRead(potPin)); 
  delay(100); 

}

void decreaseAngle() //Rotate the gearmotor in the anticlockwise direction tightening the gripper
{
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
}
void increaseAngle() //Rotate the gearmotor in the clockwise direction loosening the gripper
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
}

void doNotMove()
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
}
