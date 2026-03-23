void setup() {
  Serial.begin(9600); 
  while(!Serial){}
  Serial.print("In the setup"); 
  for(int i = 0; i<=100; i++)
  {
    Serial.print("Counting "); 
    Serial.print(i); 
    Serial.print('\n'); 
  }
  Serial.println("Setup finished"); 

}

void loop() {
  Serial.println("I'm alive"); 
  delay(500); 

}
