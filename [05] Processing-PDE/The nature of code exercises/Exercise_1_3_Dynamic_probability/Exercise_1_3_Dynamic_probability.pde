float xPos = 200; 
float yPos = 200; 
float speed = 400; 

void setup()
{
size(1000, 800); 

  
}

float direction; 

void draw()
{
  direction = random(1); 
 //background(255, 255, 200);  
  
  
  if(direction < 0.1)
  {
    xPos++; 
  }
  else if(direction < 0.2)
  {
   yPos++;  
  }
  else if(direction < 0.3)
  {
    xPos--; 
  }
  else if(direction < 0.4)
  {
   yPos--;  
  }
  else if(direction < 0.5)
  {
    
  }
  else{
     xPos+= (mouseX - xPos)/speed; 
  yPos+=(mouseY - yPos)/speed; 
  
  }
 
  fill(200, 255, 200); 
  ellipse(xPos, yPos, 3, 3); 
}
