import processing.sound.*;
SoundFile coinCollect;
SoundFile backgroundMusic;

beaver hopper;
float[] grassXs;
int stickNumber = 40;
PImage grass;
PImage jumpingHopper;
PImage happyHopper;
Stick[] sticks;

void setup()
{
  size(1200, 800);
 
  sticks = new Stick[stickNumber];
  for(int i = 0; i<stickNumber; i++)
  {
    sticks[i] = new Stick(i*40 +1100,random( 100, 600));
  }
  coinCollect = new SoundFile(this, "coinsound.mp3");
  backgroundMusic = new SoundFile(this, "Mystery-Mammal-Jingle-Bells.mp3");
  hopper = new beaver(400, 400);
  grassXs = new float[75];
  grass = loadImage("GrassBlock.png");
  for(int i = 0; i<75; i++)
  {
    grassXs[i] = (i*40);
  }
  backgroundMusic.loop();
}

void draw()
{
  background(199, 232, 255);
  
  //Static scene - ground
  fill(79, 36, 36);
  noStroke();
  rectMode(CORNER);
  rect(0, height*0.9, width, height*0.1);
  
  //Dynamic scene - grass
  for(int i = 0; i<75; i++)
  {
    imageMode(CORNER);
    image(grass, grassXs[i], height*0.85, 40, 40);
    grassXs[i]-=2;
    
    if(grassXs[i] <-40)
    {
      grassXs[i] = width;
    }
  }
  
  //Drawing sticks
  for(int i = 0; i<sticks.length; i++)
  {
    sticks[i].x--;
    hopper.checkForStickGrab(sticks[i]);
    sticks[i].drawStick();    
  }
  hopper.drawBeaver();
  
  //Movement control and stick collection
  if(keyPressed)
  {
    fill(20);
   hopper.hop();
  }
  else
  {
    hopper.fall();
  }
}
