float x = width/2;
float y = height/2;
int dotCount = 2;
int direction = 0; //0 - up,  1 - right , 2 - down, 3 - left
int radius = 6;

void setup()
{
  size(1000, 800) ;
  background(255, 255, 255);
  x = width/2;
  y = height/2;
  // frameRate(2);
}

long preMillis = millis();
int currentDots = 0;


void draw()
{
  if (currentDots < dotCount)
  {
    switch(direction)
    {
    case 0:
      y-=radius;
      break;
    case 1:
      x+=radius;
      break;
    case 2:
      y+=radius;
      break;
    case 3:
      x-=radius;
      break;
    default:
      break;
    }
    noStroke();
    fill(random(0, 255), random(0, 255), random(0, 255));
    ellipse(x, y, radius, radius);
    ++currentDots; 
  } else
  {
    dotCount+=1;
    direction = (++direction)%4;
    currentDots = 0; 
  }
}
