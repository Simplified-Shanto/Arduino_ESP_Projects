class beaver
{
  float x;
  float y;
  PImage jumpingHopper;
  PImage happyHopper;
  PImage Hopper;
  int sticks = 0;
  
  beaver(float X, float Y)
  {
    x = X;
    y = Y;
     jumpingHopper = loadImage("Hopper-Jumping.png");
  happyHopper = loadImage("Hopper-Happy.png");
    Hopper = happyHopper;
  }
  
  void drawBeaver()
  {
    y = constrain(y, 0, height - 100);
    image(Hopper, x, y, 100, 100); 
  }
  
  void hop()
  {
    Hopper = jumpingHopper;
    y-=5;
  }
  
  void fall()
  {
    Hopper = happyHopper;
    y+=5;
  }
  
  void checkForStickGrab(Stick stick)
  {
    if(stick.x >= this.x && stick.x <= (this.x + 40) && stick.y >= this.y && stick.y <= (this.y + 40))
    {
        stick.x-=1200;
        this.sticks++;
        
    }
  }
     
}
