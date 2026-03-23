const int xPin = A0; 
const int yPin = A1; 
const int buttonPin = 3; 

void setup() {
  pinMode(xPin, INPUT); 
  pinMode(yPin, INPUT); 
  pinMode(buttonPin, INPUT); 
  Serial.begin(9600); 

}

void loop() {
  int xVal = map(analogRead(xPin), 0, 1023, 0, 100); 
  int yVal = map(analogRead(yPin), 0, 1023, 0, 100); 
  
  Serial.print("X = "); 
  Serial.println(xVal); 
  Serial.print("Y = "); 
  Serial.println(yVal); 

  if(digitalRead(buttonPin)!=0)
  {
    delay(300); 
    Serial.println("Onboard button PRESSED!"); 
  }
  Serial.println(); 
  
  delay(500); 

}
