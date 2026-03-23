const int signalPin = 8; 
const int offLedPin = 12; 
const int offButton = 7; 


void shutDown()
{
for(int i = 1; i<=3; i++)
{
  digitalWrite(offLedPin, HIGH); 
  delay(500); 
  digitalWrite(offLedPin, LOW); 
  delay(500); 
}
digitalWrite(signalPin, LOW); 
}


void setup() {
  pinMode(signalPin, OUTPUT); 
  pinMode(offLedPin, OUTPUT); 
  pinMode(offButton, INPUT); 

  digitalWrite(signalPin, HIGH); 
}



void loop() {
  if(digitalRead(offButton)!=0) {delay(200); 
  digitalWrite(13, LOW); 
  shutDown(); }


    //We will blink the built in LED on pin-13 to show that the Arduino is doing something. 
    digitalWrite(13, HIGH); 
    delay(100); 
    digitalWrite(13, LOW); 
    delay(100); 
  

}
