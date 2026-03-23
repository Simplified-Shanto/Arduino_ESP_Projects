void drawRadar(float angle, int distance, float direction)
{
  fill(41, 207, 44); 
  strokeWeight(2); 
  stroke(41, 207, 44); 
  line(0, 820, 1600, 820); 
  //Drawing the reading below the main radar. 
  int textHeight = 870; 
  text("Angle: ", 950, textHeight); 
  text(angle + "°", 1070, textHeight);
  text("Distance: ",  1200, textHeight); 
  text(distance, 1370, textHeight); 
  text("cm", 1440, textHeight); 
  
  
  pushMatrix(); 
  translate(width/2, height - 80); 
  
  //Drawing the fading pointer. 
   pushMatrix();
  rotate(radians(-(angle))); 
  strokeWeight(3); 
 
   
   float Direction = direction/abs(direction); //Either 1 or -1
   float alpha; 
   if(Direction==1)
   {
    alpha = 255;  
   }
   else { alpha = 0; }
   float alphaChange = 2.83333*Direction; 
  for(int i = 1; i<=min(angle, 90); i++)
  {
    stroke(41, 207, 44, alpha); 
    rotate(radians(1)); 
    alpha-=alphaChange; 
  if(angle - i<=180)
  {
  line(0, 0, 780, 0); 
  }
  }
  popMatrix(); 
  
   stroke(41, 207, 44); 
  //Drawing those curves.
  noFill(); 
  int arcRadius = 1480; 
  int gap = 340; 
  for(int i = 0; i<=3; i++)
  {
     arc(0, 0, arcRadius - gap*i, arcRadius-gap*i, -PI, 0);
  }
  
  
  textSize(30); 
  
  int rayLength = 780; 
  rotate(PI/3); 
  for(int i = 0; i<=4; i++)
  {
     line(0, 0, 0, -rayLength); 
  text(str(30 + 30*i) + "°", -15, -rayLength-10); 
   rotate(-PI/6);  
  }
    popMatrix(); 
}



void setup()
{
 size(1600, 900); 
 
 
}

long lastCalc = millis();
float Angle = 0; 
float change = 0.5; 

void draw()
{
  background(0); 
  
  if(millis() - lastCalc > 10)
  {
    Angle+=change; 
    lastCalc = millis(); 
  }
  if(Angle > 270 || Angle < 0)
  {
   change*=(-1);  
  }
  
  drawRadar(Angle, 20, change); 
}
