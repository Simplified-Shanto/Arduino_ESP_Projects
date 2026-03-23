class colorBall
{
  float x ; //Abscissa of the ball. 
  float y ; //Ordinate of the ball. 
 
  color ballColor; //Current color of the ball/circle. 
  long lastCalc; //The last time we changed currentRadius and Transparency. 
  float Transparency ; //The transparency level of the circle. 
  float currentRadius ; //The radius at which the circle is being displayed
  float radiusThreshold; //The maximum radius it will reach before disappearing. 
  
  
  colorBall()
  {
    this.x = random(0, width); 
    y = random(0, height); 
    ballColor = color(0, 157, 255); 
    lastCalc = millis(); 
    Transparency = 100; 
    currentRadius = 0; 
    radiusThreshold = random(100, 200); 
    
  }
  
 
  void update()
  {
   
   if(millis() - this.lastCalc > timeThresh)
   {
      
    if(this.currentRadius > this.radiusThreshold)
    {
    this.radiusThreshold = random(20, 150);  
    this.x = random(0, width); 
    this.y = random(0, height); 
    this.Transparency = 0; 
    this.currentRadius = 0; 
    }
    
     
     this.Transparency+=(255/this.radiusThreshold); 
   this.currentRadius+=1; 
   this.lastCalc = millis(); 
   }
  noStroke(); 
  fill(0, 64, 255, 255 - this.Transparency); 
  ellipse(this.x, this.y, this.currentRadius, this.currentRadius); 
  
   
  
  
  
  
 
  
}
  
  
}; 
