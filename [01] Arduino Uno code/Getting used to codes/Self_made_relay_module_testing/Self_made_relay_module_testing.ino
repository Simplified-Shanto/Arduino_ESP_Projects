
#define signalPin  8
#define potPin A0
void setup() {
  // put your setup code here, to run once:
  pinMode(signalPin, OUTPUT); 
  pinMode(potPin, INPUT); 
}

void loop() {
  int reading = analogRead(potPin); 
  int wait = map(reading, 0, 1023, 0, 2000); 
  
  digitalWrite(signalPin, HIGH); 
  delay(wait); 
  digitalWrite(signalPin, LOW); 
  delay(wait); 
  // put your main code here, to run repeatedly:

}
