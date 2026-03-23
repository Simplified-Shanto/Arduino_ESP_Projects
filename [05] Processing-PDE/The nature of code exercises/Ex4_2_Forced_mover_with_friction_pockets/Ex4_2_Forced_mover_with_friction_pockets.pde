Mover[] movers = new Mover[20];

//Objective: To add check edge functions.

void setup() {
  size(1000, 800);
  smooth();
  background(255);

  for (int i = 0; i < movers.length; i++)
  {
    movers[i] = new Mover(random(0.1, 5), 0, 0);
  }
}




void draw()
{
  background(255);
  fill(220, 200, 250); 
  noStroke(); 
  rect(0, 0, width/2, height/2); 

  for (int i = 0; i < movers.length; i++)
  {
    float m = movers[i].mass; 
    PVector wind = new PVector(0.01, 0); 
    PVector gravity = new PVector(0, 0.1*m); 
    
    PVector friction = movers[i].velocity.get(); //We want the velocity to be intact, so just making a copy
    friction.normalize(); //Friction is not directly proportional to the velocity. 
    friction.mult(-1);   //Friction acts in the opposite direction to the velocity. 
    float c = 0.01;       //Coefficient of friction.
    
   
    friction.mult(c); 
    
    movers[i].applyForce(friction); //Friction force of air molecule. 
    movers[i].applyForce(wind); 
    movers[i].applyForce(gravity); 
    movers[i].update();
    movers[i].checkEdges();
    movers[i].display();
  }
}







class Mover {
  PVector location;
  PVector velocity;
  PVector acceleration;
  float   mass; 

  Mover(float m, float x, float y) {
    location = new PVector(x, y);
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0); 
    mass = m; 
  }
  
  void applyForce(PVector force)
  {
    PVector f = PVector.div(force, mass); 
    acceleration.add(f); 
  }

  void update() {
    velocity.add(acceleration); 
    location.add(velocity); 
    
    acceleration.mult(0); 
  }

  void display() {
    stroke(0);
    fill(175);
    ellipse(location.x, location.y, mass*16, mass*16);
  }
  
  void checkEdges() {
    if (location.x > width) {
      velocity.x = -1*velocity.x;
      location.x = width; 
    } else if (location.x < 0) {
      velocity.x = -1*velocity.x; 
      location.x = width; 
    }
    if (location.y > height) {
      velocity.y = -1*velocity.y; 
      location.y = height; 
    } else if (location.y < 0) {
      velocity.y = -1*velocity.y; 
      location.y = height; 
    }
  }
}
