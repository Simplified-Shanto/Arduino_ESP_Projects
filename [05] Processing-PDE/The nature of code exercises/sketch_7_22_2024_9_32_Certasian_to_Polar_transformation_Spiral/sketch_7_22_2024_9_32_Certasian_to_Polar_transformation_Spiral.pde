float radius = 1; 
float angle = 0; 

void setup()
{
  size(1000, 800); 
  background(255, 255, 255); 
}

void draw()
{
  
  float x = radius*cos(radians(angle)); 
  float y = radius*sin(radians(angle));
  
  fill(0, 0, 0); 
  
  
  translate(width/2, height/2); 
 // strokeWeight(1); 
  fill(random(0, 255), random(0, 255), random(0, 255)); 
  noStroke(); 
  ellipse(x, y, 10, 10); 
  radius+=0.1; 
  angle+=1.5; 
  
  
  
  
  
}
  
