class Mover
{
  PVector position = new PVector(random(width), random(height));
  PVector velocity = new PVector(0, 0);
  PVector acceleration = new PVector(0, 0);
  float rateOfAcceleration = 0.2;
  float velocityLimit = 5;
  float moverRadius = 10;
  
  
  //Function for updating the Mover and fixing its direction
  void update()
  {
    PVector mouse = new PVector(mouseX, mouseY);
    PVector direction = PVector.sub(mouse, position);
    direction.normalize();
    direction.mult(rateOfAcceleration);
   acceleration = direction;
   
   velocity.add(acceleration);
   velocity.limit(velocityLimit);
   position.add(velocity);
  }
  //Function for checking whether our mover is touching the edges or not
  void checkEdges()
  {
    if(position.x<0)
    {
      position.x = width;
    }
    else if(position.x>width)
    {
      position.x = 0;
    }
    if(position.y<0)
    {
      position.x = height;
    }
    else if(position.y>height)
    {
      position.y = 0;
    }
  }
  
  //Function for displaying Mover at its position
  void display()
  {
    strokeWeight(2);
    fill(150);
    ellipse(position.x, position.y, moverRadius, moverRadius);
  }
  
  
  
};
