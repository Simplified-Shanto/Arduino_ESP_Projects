Walker walkman;
void setup()
{
  size(1000, 800);
  walkman = new Walker();
  background(255);
  walkman.speed = 3;
  walkman.body = 5;
  walkman.steps = millis();
}

void draw()
{
 walkman.speed = 5;
  walkman.appear();
  walkman.step();
}

class Walker
{
  int x;
  int y;
  int speed;
  int body;
  int steps;  // How many steps our walker has already taken
  int prevX;
  int prevY;
  boolean drawing;
  Walker()
  {
    x = width/2;
    y = height/2;
    speed = 1;
    body = 2;
    steps = 0;
    prevX = 0;
    prevY = 0;
    drawing = false;
  }
  void step()
  {
    x = int(random(width));
    y = int(random(height));
   
  }
  
  void appear()
  {
    println(millis()/1000);
    if((millis() - steps) > 500)
    {
steps = millis();
strokeWeight(2);
    stroke(random(255), random(255), random(255));
    line(x, y, prevX , prevY);
    prevX = x;
    prevY = y;
    noStroke();
    fill(random(255), random(255), random(255));
    ellipse(x, y, body, body);
    }
  }
 
}
