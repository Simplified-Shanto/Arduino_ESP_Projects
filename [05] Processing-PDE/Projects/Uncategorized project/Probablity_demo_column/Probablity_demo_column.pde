rectangle[] rects;
int noc = 30;
void setup()
{
  size(1000, 800);
  rects = new rectangle[noc];
  for(int i = 0; i<noc; i++)
  {
    rects[i] = new rectangle(i*width/noc); 
  }
  
}
void draw()
{
  background(255, 255, 255);
  for(int i = 0; i<noc; i++){    
  rects[i].drawRect();
  }
  
  rects[floor(random(noc))].Height++;
  
}

class rectangle
{
  public
    float Height = 10;
    float y = height - Height;
    float Width  = width/noc - 2;
    float x;
    
    rectangle(float xAxis)
    {
        x = xAxis;
    }
    
    void drawRect()
    {
      fill(100);
      y = height - Height;
      noStroke();
      rect(x, y, Width, Height);
    }
  
}
