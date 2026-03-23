PVector mouse, corner;
float xTrans = 0;
float yTrans = 0;
void setup()
{
  size(1200, 800);
  mouse = new PVector(mouseX, mouseY);
  corner = new PVector(width/2, height/2);
}

void draw()
{
  
  background(255, 230, 230);
  mouse.x = mouseX;
  mouse.y = mouseY;
  
  stroke(0, 220, 0);
  strokeWeight(3);
  
  mouse.normalize();
  line(mouse.x, mouse.y, corner.x, corner.y);
  if(mousePressed)
  {
    corner.x+=5;
  }
  
   
  
  
  
}
