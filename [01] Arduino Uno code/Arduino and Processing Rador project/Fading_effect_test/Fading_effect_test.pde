void setup()
{
 size(800, 400);  
  
}


void draw()
{
  background(255, 255, 255); 
  
  stroke(148, 49, 247, 30); 
  strokeWeight(8); 
  int alpha = 255; 
  for(int i = 5; i<=800; i+=15)
  {
    stroke(148, 49, 247, alpha);
   line(i, 0, i, 400); 
   alpha-=6; 
  }
}
