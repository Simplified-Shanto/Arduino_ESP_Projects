#define en2 10
#define in3 12
#define in4 13


void setup() {
 pinMode(en2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 

}

void loop() { 
analogWrite(en2, 150); 

digitalWrite(in3, HIGH); 
 digitalWrite(in4, LOW); 
delay(2000); 

digitalWrite(in3, LOW); 

delay(2000); 

digitalWrite(in4, HIGH); 

delay(2000); 

digitalWrite(in3, HIGH); 

}
