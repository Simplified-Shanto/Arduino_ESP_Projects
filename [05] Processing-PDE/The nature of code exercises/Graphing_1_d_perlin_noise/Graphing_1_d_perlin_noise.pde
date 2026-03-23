float tX = 0; 
float change = 0.01; 
float curveWidth = 8; //in pixel


void setup()
{
 size(1000, 800);  
  background(255); 
  
  
}

float rectH; //Height of the rectangle we'll be drawing.
float tranVal = change; 
float bav  = 1; 

void draw()
{
  rectH = noise(tX); 
  rectH = map(rectH, 0, 1, 0, width); 
  
  pushMatrix();
  
  if(tX > width)
  {
    translate(-tranVal, 0); 
    tranVal+=change; 
  }
  
  noStroke(); 
  fill(0); 
  // rect(0, tX*100, rectH, 1); //For vertical curve
 rect(tX*100, 0, 1, rectH, bav); //For horizontal curve
  
  fill(255, 255, 255); 
  //rect(0, tX*100, rectH - curveWidth, 2); //For Vertical curve
 rect(tX*100, 0, 1, rectH - curveWidth, bav); //For horizontal curve. 
  
  tX+=change; 
  
  popMatrix(); 
}
