//Objective: To simulate an square object sliding down an inclined plane with variable angles
/* mass of the object and gravitational acceleration.
 
 
 */


Slider massSlider = new Slider(20, 700, 0, 100, "Mass(kg)");
//inclination angle slider
Slider IAngleSlider =  new Slider(20, 650, 0, 95, "Inclination(deg)");
//gravitational acceleration slider.
Slider GAslider = new Slider(20, 750, 0, 9.8, "g(m/s^2)");

float plankLength = 400;
float IAngle = 0; //Inclination angle.

PVector location;
PVector velocity;
PVector acceleration;

void setup()
{
  size(1000, 800);
  location = new PVector(0, 0);
  velocity = new PVector(0, 0);
  acceleration = new PVector(-0.2, 0);
}

PVector pivotPosition = new PVector(200, 500); //Considering it a pivot since we have the mobility to change the angle.
PVector boxDimensions = new PVector(100, 100);
PVector boxPosition = new PVector(plankLength - boxDimensions.x, -boxDimensions.y);
PVector force;

float dashLength = 12;
int flag = 0; 

void draw()
{
  background(255);



  massSlider.drawSlider();
  GAslider.drawSlider();
  IAngleSlider.drawSlider();

  IAngle = IAngleSlider.sliderValue;

  strokeWeight(1);
  line(pivotPosition.x - 100, pivotPosition.y, 700, pivotPosition.y);


  pushMatrix();
  translate(pivotPosition.x, pivotPosition.y);
  rotate(radians(-IAngle));
  strokeWeight(2);
  
  if(keyPressed)  //Starting the action once dictated by a keypress
  {
    flag = 1 ;
  }
  
 
  
  if(flag==1)
  {
  float mu = 0.08;  //Coefficient of friction
  float g = GAslider.sliderValue; 
  float gX = g*sin(radians(IAngle)); //Horizontal component of the gravitational force. 
  float gY = g*cos(radians(IAngle)); //Normal force
  force = new PVector(-gX + gY*mu, 0);  // No vertical displacement considering the plank as the horizon
  force.x = min(force.x, 0); 
  acceleration = PVector.div(force, massSlider.sliderValue); 
  
  velocity.add(acceleration); 
  boxPosition.add(velocity); 
  }
  
  
  // line(pivotPosition.x, pivotPosition.y,  pivotPosition.x +  plankLength*cos(radians(IAngle)),pivotPosition.y - plankLength*sin(radians(IAngle)));
  line(0, 0, plankLength, 0);
  fill(255, 200, 100);
  
  if(boxPosition.x < 0) //box returns to initial position after one fall. 
  {
    boxPosition.x = 0; 
    delay(1000); 
    boxPosition.x = plankLength - boxDimensions.x; 
    flag = 0; 
    acceleration.mult(0); 
    velocity.mult(0); 
  }
  
  rect(boxPosition.x, boxPosition.y, boxDimensions.x, boxDimensions.y);
  popMatrix();


  float plankEndX = pivotPosition.x +  plankLength*cos(radians(IAngle));
  float plankEndY = pivotPosition.y - plankLength*sin(radians(IAngle));
  float vdl =  pivotPosition.y - plankEndY;  //Vdl = length of the vertical dashed line

   
  for (float y = pivotPosition.y - vdl%6; y > plankEndY; y-= dashLength*2)
  {
    stroke(0, 0, 0);
    strokeWeight(1);

    if (y > plankEndY)
    {
      line(plankEndX, y, plankEndX, y-dashLength);
    }
  }
  
}
