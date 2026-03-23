#include<Keypad.h>
const byte rows = 4; 
const byte cols = 4; 

char hexaKeys[rows][cols] = 
{
  
}; 

byte rowPins[rows] = {9, 8, 7, 6}; 
byte colPins[cols] = {5, 4, 3, 2}; 

Keypad matrixKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, rows, cols); 


void setup() {
  Serial.begin(9600); 

}

void loop() {
  char responseKey = matrixKeypad.getKey(); 

  if(responseKey)
  {
    Serial.println(responseKey); 
  }
  

}
