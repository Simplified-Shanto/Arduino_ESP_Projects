class Mover
{
  PVector position;
  PVector acceleration;
  PVector velocity;
  float mass;

  Mover(int x, int y, float m)
  {
    position = new PVector(x, y);
    acceleration = new PVector(0, 0);
    velocity = new PVector(0, 0);
    mass = m;
  }
  
  void applyForce(PVector force){
  PVector f = PVector.div(force, mass);
  acceleration.add(f); 
  };
  
  void checkEdges()
  {
    if(position.x > width)
    {
      position.x = width;
      velocity.x*=-1;
    } else if(position.x < 0)
    {
      position.x = 0;
      velocity.x*=-1;
    }
    if(position.y > height)
    {
      position.y = height;
      velocity.y*=-1;
    }
  }
  
  
  void update()
  {
    this.velocity.add(acceleration);
    this.position.add(velocity);
    this.acceleration.mult(0); 
  }
  
  
  void display()
  {
    stroke(0);
    strokeWeight(2);
   fill(255, 255, 255, 127);
    ellipse(position.x, position.y, mass*30, mass*30); 
  }
  
};
