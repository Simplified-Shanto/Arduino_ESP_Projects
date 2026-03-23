Walker walkman;
void setup()
{
  size(1000, 800);
  walkman = new Walker();
  background(255);
  walkman.speed = 3;
  walkman.body = 5;
}

void draw()
{
  walkman.speed = int(random(10));
  walkman.appear();
  walkman.step();
}

class Walker
{
  int x, y,speed,body;
  
  Walker()
  {
    x = width/2;
    y = height/2;
    speed = 1;
    body = 2;
  }
  
  void step()
  {
    int choice = int(random(4));
    if(choice == 1)
    x+=speed;
    else if(choice == 2)
    x-=speed;
    else if(choice == 3)
    y+=speed;
    else if(choice == 0)
    y-=speed;
    x = constrain(x, 0, width-1);
    y = constrain(y, 0, height-1);
  }
  void appear()
  {
    noStroke();
    fill(random(255),random(255), random(255));
    ellipse(x, y, body, body);
  }
}
