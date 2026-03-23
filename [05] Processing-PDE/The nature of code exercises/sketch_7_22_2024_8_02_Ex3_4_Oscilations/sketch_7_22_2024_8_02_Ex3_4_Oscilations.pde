float angle = 0; 
float aVelocity = 0; 
float aAcceleration = 0.001; 


void setup()
{
  size(1000, 800); 
  
}


float radius = 30; 

void draw()
{
 background(0, 200, 100); 
 
 fill(200, 100, 100); 
 rectMode(CENTER); 
 
 translate(width/2, height/2); 
 rotate(angle);
 stroke(0); 
 strokeWeight(2);
 line(0, -100, 0, 100); 
 ellipse(0, -100, radius, radius); 
 ellipse(0, 100, radius, radius); 

 
 aVelocity+=(aAcceleration); 
 angle+=aVelocity; 
 
 
  
}
