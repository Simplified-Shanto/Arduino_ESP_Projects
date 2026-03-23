//Author: Nayeem Islam Shanto
//Intended board: AI thinker ESP32 code
//Sketch started: 10/21/2023. //Month/day// year. 

#define flashLedPin 4

void setup()
{
  pinMode(flashLedPin, OUTPUT); 
}



void loop()
{
       digitalWrite(flashLedPin, HIGH); 
       delay(2000); 
       digitalWrite(flashLedPin, LOW); 
       delay(2000); 
}
