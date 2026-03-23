float tX = 0; 
float change = 0.01; 
float curveWidth = 8; //in pixel


void setup()
{
 size(1000, 800);  
  background(255); 
  
}

float rectH; //Height of the rectangle we'll be drawing.
float bav  = 1; 

float prevX = 0; 
float prevY = 200; 

void draw()
{
  rectH = noise(tX); 
  rectH = map(rectH, 0, 1, 0, width); 
   tX+=change; 
   
   strokeWeight(3); 
  line(prevX, prevY, tX, rectH); 
  prevX = tX; 
  prevY = rectH; 
 

}
