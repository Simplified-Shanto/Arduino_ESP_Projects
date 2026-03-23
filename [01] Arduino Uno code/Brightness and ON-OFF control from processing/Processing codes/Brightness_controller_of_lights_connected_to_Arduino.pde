/*
Created: 17-10-2022
Last updated: 20-10-2022
Author: Nayeem Islam Shanto (islamshafiul386@gmail.com)

This code controls the ON/OFF state and brightness of an LED strip connected to the Arduino. 
Press the toggle switch to turn the light ON/OFF. 
Drag the Slider to control the brightness of the LED strip. 
*/

import processing.serial.*; 

Slider brightness; 
Toggle Switch; 
Serial port; 


String portName = Serial.list()[0]; 
int toSend = 0; 
int sent = 0; 
float val; 


void setup()
{
  size(400, 400); 
  port = new Serial(this, portName, 9600);  
  brightness = new Slider(50, 350, 250, 20, color(252, 200, 3)); 
  Switch = new Toggle(100, 100); 
}


//Objective: To send the x position of the point to control the brightness of led on Arduino. 
void draw()
{
  background(157, 244, 252); 
  brightness.drawSlider(); 
  Switch.drawToggle(); 
  
   val = brightness.sliderValue; 
  toSend = round(map(val, 0 ,100,  0, 250)) * Switch.state;
  //if Switch.state==0, then toSend = 0
 
  
  if(sent!=toSend)    //We are doing this not to keep the Serial port busy all the time. 
                      //We'll only send a PWM value, only when some new value is generated. 
  {
    sent = toSend; 
    String str =  str(sent);  
    port.write(str);
    port.write('\n');
  }
  stroke(0, 0, 0); 
  strokeWeight(2); 
  textSize(50); 
  text("PWM = ", 100, 250); 
  text(toSend,300, 250); 
  
}
    
  
