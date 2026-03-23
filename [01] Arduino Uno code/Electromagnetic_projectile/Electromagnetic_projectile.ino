#define signalPin  8

int gap = 500; 
String command = "a"; 

void setup() {
  pinMode(signalPin, OUTPUT); 
  Serial.begin(9600); 

}

void loop() {
  if(Serial.available())
  {
    command = Serial.readStringUntil('.'); 
    command = command.substring(0, command.length()); 
    gap = command.toInt(); 
     digitalWrite(signalPin, HIGH); 
  delay(gap); 
  digitalWrite(signalPin, LOW); 
  }

 


}
