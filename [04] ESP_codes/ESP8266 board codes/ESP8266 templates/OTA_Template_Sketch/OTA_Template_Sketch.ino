#include "OTA.h"

//Functionality for our code
#define ledPin D0
unsigned long preMillis = 0; 
const long interval1 = 700; 
const long interval2 = 100; 
int ledState = HIGH; 
//Objective: The led will glow in the pattern 700-700-700-200-200-200 //these are the delays between two successive blinks. 
int switchings = 0; //The number of times we've switched the ledState . switchings/2 = number of blinks. 


void setup() {
 Serial.begin(115200); 
 Serial.println("Booting"); 
   pinMode(LED_BUILTIN, OUTPUT); 
  

 ArduinoOTA.setHostname("TemplateSketch"); 
 setupOTA(); 
 
  //your code

}

void loop() {
  ArduinoOTA.handle(); 

  //your code

  if(switchings < 6)
  {
  if(millis() - preMillis >= interval1)
  {
    preMillis = millis(); 
    ledState = not(ledState); 
    digitalWrite(LED_BUILTIN, ledState); 
    switchings++; 
    
  }
  }
  else if(switchings < 12)
  {
    if(millis() - preMillis >= interval2)
    {
      preMillis = millis(); 
      ledState = not(ledState); 
      digitalWrite(LED_BUILTIN, ledState); 
      switchings++; 
    }
  }
  else 
  {
    switchings = 0; 
  }
  
  // digitalWrite(LED_BUILTIN, HIGH);
}
