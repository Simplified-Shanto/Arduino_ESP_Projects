Mover[] balls;
int howMany = 20;
void setup()
{
  size(800, 600);
  
  balls = new Mover[howMany];
  for(int i = 0; i<howMany; i++)
  {
    balls[i] = new Mover();
  }
}

void draw()
{
  background(255);
  for(int i = 0; i<howMany; i++)
  {
  balls[i].update();
  //balls[i].checkEdges();
  balls[i].display();
  }
}
