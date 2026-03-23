//Objective: to simulate a simple pendulum 

float bobRadius = 10; 
float stringLength = 200; 
float amplitude = 200; 
float T = 4; 
float x = width/2; 
float y = height/2; 

void setup()
{
  size(1000, 800); 
  
}

void draw()
{
  background(255, 255, 255); 
   x = amplitude*sin(radians((TWO_PI/T)*frameCount)); 
   y = stringLength*cos(asin(x/stringLength)); 
   strokeWeight(2); 
   translate(width/2, height/2); 
   line(0, 0, x, y); 
   strokeWeight(1); 
   fill(0, 200, 255); 
   ellipse(x, y, bobRadius, bobRadius); 
  //println(x); 
   
}
