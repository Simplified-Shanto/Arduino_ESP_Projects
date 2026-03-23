//Change those two variables to make changes to the animation. 
int timeThresh = 30; //How fast the animation changes. (in millisecond)
int nob = 100; //Number of balls. 

colorBall[] balls;

void setup()
{
  balls = new colorBall[nob]; 
 size(800, 800); 
 
 for(int i = 0; i<nob; i++)
{
  balls[i] = new colorBall(); 
}

}



void draw()
{
  background(255, 255, 255); 
  
  for(int i = 0; i<nob; i++)
  {
   balls[i].update();  
  }
}
