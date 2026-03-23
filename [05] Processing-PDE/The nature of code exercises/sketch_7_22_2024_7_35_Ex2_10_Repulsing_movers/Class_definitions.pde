class Mover {
  PVector location;
  PVector velocity;
  PVector acceleration;
  
  float   mass;
  float   radius;
  
  
  float angle;
  float aVelocity; 
  float aAcceleration; 

  Mover(float r, float x, float y) {
    location = new PVector(x, y);
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0);
    
    radius = r;
    mass = radius;
    
    angle = 0; 
    aVelocity = 0; 
    aAcceleration = 0.0001; 
  }

  void applyForce(PVector force)
  {
    PVector f = PVector.div(force, mass);
    acceleration.add(f);
  }


  void update() {
    velocity.add(acceleration);
    location.add(velocity);
    aAcceleration = (acceleration.x/100); 
    acceleration.mult(0);
    
    
    
    aVelocity+=aAcceleration; 
    angle+=aVelocity; 
  }

  void display() {
    stroke(0);
    fill(175);
    rectMode(CENTER);
    pushMatrix(); 
     
    translate(location.x, location.y);  
    rotate(angle);
    rect(0, 0, radius, radius); 
     
    popMatrix(); 
    
  }

  PVector attract(Mover m)
  {
    float G  = 0.4;
    PVector force = new PVector(0, 0);
    force = PVector.sub(location, m.location); //Direction of mover from the attractor
    float distance = force.mag();   //Distance between attractor and mover
    distance = constrain(distance, 5, 25);
    force.normalize();
    float strength = (G*mass*m.mass) / (distance * distance);
    force.mult(strength);
    return force;
  }


  void checkEdges() {
    if (location.x > width) {
      velocity.x = -1*velocity.x;
      location.x = width;
    } else if (location.x < 0) {
      velocity.x = -1*velocity.x;
      location.x = 0;
    }
    if (location.y > height) {
      velocity.y = -1*velocity.y;
      location.y = height;
    } else if (location.y < 0) {
      velocity.y = -1*velocity.y;
      location.y = 0;
    }
  }
}




class attractor
{
  float mass;
  PVector location;
  float G;

  attractor()
  {
    location = new PVector(random(100, width - 100), random(100, height - 100));
    mass = 20;
    G = 0.4;
  }

  PVector attract(Mover m)
  {
    PVector force = new PVector(0, 0);
    force = PVector.sub(location, m.location); //Direction of mover from the attractor
    float distance = force.mag();   //Distance between attractor and mover
    distance = constrain(distance, 5, 25);
    force.normalize();
    float strength = (G*mass*m.mass) / (distance * distance);
    force.mult(strength);
    return force;
  }

  void drawAttractor()
  {
    fill(200, 20, 20);
    ellipse(location.x, location.y, mass*3, mass*3);
  }
}
