const int ledPin = 8; 
const int signalPin1 = 7; 
const int signalPin2 = 6; 
int state = 0; 


void setup()
{
 
pinMode(ledPin, OUTPUT); 
pinMode(signalPin1, OUTPUT); 
pinMode(signalPin2, OUTPUT); 

digitalWrite(signalPin1, HIGH); 
digitalWrite(signalPin2, HIGH); 


digitalWrite(ledPin, HIGH); 
delay(500); 
digitalWrite(ledPin, LOW); 
delay(500); 
digitalWrite(ledPin, HIGH); 
delay(500); 
digitalWrite(ledPin, LOW); 
delay(500); 


digitalWrite(ledPin, HIGH); 
delay(500); 
digitalWrite(ledPin, LOW); 
delay(500); 
digitalWrite(ledPin, HIGH); 
delay(500); 
digitalWrite(ledPin, LOW); 
delay(500); 



delay(1000); 


  digitalWrite(signalPin1, LOW); 
  digitalWrite(signalPin2, LOW); 
}


void loop()
{
   
  
}
