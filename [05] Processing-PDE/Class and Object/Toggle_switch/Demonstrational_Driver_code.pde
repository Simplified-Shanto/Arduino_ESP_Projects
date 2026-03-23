/*
Created: 20/10/2022
Last update: 20/10/2022
Author: Nayeem Islam Shanto. 

This code is mainly purposed to demonstrate the Toggle switch class. 

When the toggle is ON, the slider is visible and active. 
When the toggle is OFF, the slider isn't present in the canvas. 
Tweak the Slider to change the size of the Toggle. 

*/

void setup()
{
  size(400, 300); 
  
}


Toggle Switch = new Toggle(50, 50); 
Slider Sze = new Slider(50, 250, 300, 20, color(252, 200, 3)); 

void draw()
{
  background(131, 174, 242); 
  Switch.drawToggle(); 
 if(Switch.state==1)
 {
  Sze.drawSlider(); 
 }
  Switch.scale = (Sze.sliderValue/100.0)*5; 
  
  
}
