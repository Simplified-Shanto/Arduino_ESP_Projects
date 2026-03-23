class Walker
{
 int xPos; 
 int yPos; 
 
 Walker()
 {
  yPos = height/2; 
  xPos = width/2; 
 }
 
 void showUp()
 {
   stroke(0);
   strokeWeight(1); 
   point(this.xPos, this.yPos); 
 }
 
};

Walker bob; 

void setup()
{
  size(800, 500); 
  bob = new Walker(); 
  
}

int decision; 
int speed = 2; 

void draw()
{
 bob.showUp(); 
 
 decision = floor(random(0, 6)); 
 
 switch(decision)
 {
  case 0: bob.xPos+=speed; 
  break; 
  case 1: bob.xPos-=speed; 
  break; 
  case 2: bob.yPos+=speed; 
  break; 
  case 3: bob.yPos-=speed; 
  break; 
  case 4: bob.yPos+=speed; 
  break; 
  case 5: bob.xPos+=speed; 
  break; 
  
  default: break; 
 }
  
}
