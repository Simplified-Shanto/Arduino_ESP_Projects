#include<Keypad.h> 
const byte rows = 4; 
const byte cols = 4; 

char hexaKeys[rows][cols] = 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'} 
}; 

byte rowPins[rows] = {9, 8, 7, 6}; 
byte colPins[cols] = {5, 4, 3, 2}; 

Keypad matrixKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, rows, cols); 

void setup()
{
  Serial.begin(9600); 

  
}

KeyState state; 
void loop()
{/*
  char reading = matrixKeypad.getKey(); 
    if(reading!=NULL)
    {
      Serial.println(reading); 
    }
  
  char  reading =  matrixKeypad.waitForKey();
   Serial.println(reading);  
   Serial.println("LOOPING"); 
     */

     state = matrixKeypad.getState(); 
     if(state==HOLD)
     {
      Serial.println("HOLD"); 
     }
     if(state==RELEASED)
     {
      Serial.println("RELEASED"); 
     }
     if(state==IDLE)
     {
      Serial.println("IDLE"); 
     }
     if(state==PRESSED)
     {
      Serial.println("PRESSED"); 
     }
   
  
}
