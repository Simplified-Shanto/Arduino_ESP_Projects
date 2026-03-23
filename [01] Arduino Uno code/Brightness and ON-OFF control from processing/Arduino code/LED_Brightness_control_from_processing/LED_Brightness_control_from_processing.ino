int ledStripPin = 9; 

void setup() {
  pinMode(ledStripPin, OUTPUT); 
  Serial.begin(9600); 
}


void loop() {

 if(Serial.available()>0)
 {
    String value = Serial.readStringUntil('\n'); 
    int pwm = value.toInt(); 
    
    if(pwm >= 0 && pwm <=255)
    {
      analogWrite(ledStripPin, pwm); 
    }

     Serial.print("Recieved pwm = ") ;
     Serial.println(pwm); 
 }
  
}
