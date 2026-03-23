class Mover {
  PVector location;
  PVector velocity;
  PVector acceleration;
  float   mass;
  float   sideLength; 

  Mover(float m, float l, float x, float y) {
    location = new PVector(x, y);
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0);
    mass = m;
    sideLength = l; 
  }

  void applyForce(PVector force)
  {
    PVector f = PVector.div(force, mass);
    acceleration.add(f);
  }

  boolean isInsideLiquid(Liquid l)  
  {
    if (location.x + sideLength> l.x && location.x < l.x + l.w &&
      location.y + sideLength> l.y && location.y < l.y + l.h)    //Remember the co-ordinate system we are using here is a bit different. 
    {
      return true;
    } else
    {
      return false;
    }
  }


  void drag(Liquid l)
  {
    float speed = velocity.mag();
    float dragMagnitude = 0.1*sideLength*l.c * speed * speed;  //drag force = coefficient * speed * speed

    PVector drag = velocity.get();
    drag.mult(-1);  //Drag acts in the opposite direction of the objects velocity
    drag.normalize();   //Having only the direction
    drag.mult(dragMagnitude);   //Getting the final force.

    applyForce(drag);   //Applying the drag force.
  }

  void update() {
    velocity.add(acceleration);
    location.add(velocity);

    acceleration.mult(0);
  }

  void display() {
    stroke(0);
    fill(175, 150, 150);
    rect(location.x, location.y, sideLength, sideLength);
  }

  void checkEdges() {
    if (location.x + sideLength > width) {
      velocity.x = -1*velocity.x;
      location.x = width - sideLength;
    } else if (location.x  < 0) {
      velocity.x = -1*velocity.x;
      location.x = width;
    }
    if (location.y + sideLength> height) {
      velocity.y = -1*velocity.y;
      location.y = height - sideLength;
    } else if (location.y < 0) {
      velocity.y = -1*velocity.y;
      location.y = height;
    }
  }
}


class Liquid
{
  float x, y, w, h; //Positions and dimensions of the liquid
  float c = 0.01;

  Liquid(float x_, float y_, float w_, float h_, float c_)
  {
    x = x_;
    y = y_;
    w = w_;
    h = h_;
    c = c_;
  }

  void drawLiquid()
  {
    stroke(175);
    fill(30, 150, 200, 60);
    rect(x, y, w, h);
  }
}
