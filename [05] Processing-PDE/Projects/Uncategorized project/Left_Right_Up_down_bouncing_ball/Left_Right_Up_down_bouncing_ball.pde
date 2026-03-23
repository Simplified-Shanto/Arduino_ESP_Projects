PVector position = new PVector(100, 100);
PVector velocity = new PVector(2, 5);

void setup()
{
 size(1200, 800);
 
  
}

void draw()
{
 background(155, 200, 100);
 position.add(velocity);
 
 if(position.x > width || position.x < 0)
 {
   velocity.x*=-1;
 }
 if(position.y > height || position.y < 0)
 {
   velocity.y*=-1;
 }
 
 fill(255, 20, 255);
 noStroke();
 ellipse(position.x, position.y, 40, 40);
  
}
