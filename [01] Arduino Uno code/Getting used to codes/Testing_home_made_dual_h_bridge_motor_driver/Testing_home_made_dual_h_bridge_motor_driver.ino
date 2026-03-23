#define en1 3
#define in1 2
#define in2 4

#define en2 5
#define in3 6
#define in4 7

void setup() {
  pinMode(en1, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 

  pinMode(en2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  

}

void loop() {
analogWrite(en1, 150); 
analogWrite(en2, 150); 


digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 

 digitalWrite(in3, HIGH); 
 digitalWrite(in4, LOW); 
delay(2000); 

digitalWrite(in2, HIGH); 
digitalWrite(in4, HIGH); 
delay(2000); 

digitalWrite(in1, LOW); 
digitalWrite(in3, LOW); 

delay(2000); 

digitalWrite(in3, HIGH); 
digitalWrite(in1, HIGH); 
delay(2000); 

}
