float t = 100;

void setup()
{
  size(1000, 800);
  
}

void draw()
{
  background(255);
  fill(133);
  
  t+=0.005;
  float x = noise(t);
  float y = noise(t);
  x = map(x, 0, 1, 0, width);
  y = map(y, 0, 1, 0, height);
  ellipse(x, y, 30, 30);
  
  
}
