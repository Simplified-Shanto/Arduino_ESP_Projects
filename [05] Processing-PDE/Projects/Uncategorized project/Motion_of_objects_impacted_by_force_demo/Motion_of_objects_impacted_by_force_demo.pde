PVector gravity = new PVector(0, 0.1);
PVector wind = new PVector(0.01, 0);
Mover ball;
Mover[] balls;
void setup()
{
  size(800, 600);
  ball = new Mover(100, 200, 1);
  balls = new Mover[20];
  for(int i = 0; i<20; i++)
  {
    balls[i] = new Mover(50,100, random(0.3,3));
  }
}

void draw()
{
  
  background(100, 100, 100);
  for(int i = 0; i<balls.length; i++)
  {
  balls[i].applyForce(wind);
  balls[i].applyForce(gravity);
  balls[i].update();
  balls[i].checkEdges();
  balls[i].display();
  }
}
