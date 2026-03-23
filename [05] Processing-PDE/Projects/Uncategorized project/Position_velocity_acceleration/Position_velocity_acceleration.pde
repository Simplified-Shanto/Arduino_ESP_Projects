PVector position = new PVector(400, height - 50);
PVector velocity = new PVector(0,0.1);
PVector acceleration = new PVector(0, 0.1);

void setup()
{
   size(1200, 800);
}

void draw()
{
  background(100, 200, 250);
  stroke(100, 100, 250);
  strokeWeight(3);
  fill(50, 200, 100);
  ellipse(position.x, position.y, 30, 30);
  velocity.add(acceleration);
  position.add(velocity);
}
