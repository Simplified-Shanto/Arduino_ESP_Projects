
class Slider{
  PVector position; 
  float sliderHeight; 
  float sliderWidth; 
  float sliderValue; 
  color sliderColor; 
  
  float bavel = 90; 
  
  float ballX = 0; 
  float ballRadius = 0; 
  float ballY = 0;
  
  Slider(float x, float y, float w, float h, color c)
  {
    position = new PVector(x, y); 
    sliderWidth = w; 
    sliderHeight = h; 
    sliderColor = c;  
    ballX = x + w/4.0; 
    ballY = y + h/2.0; 
    ballRadius = 1.5*h;
    
  }
  
  void drawSlider()
  {
   //Rendering Slider value. 
   this.sliderValue = ((this.ballX - this.position.x)/this.sliderWidth)*100.00; 
   
    //Checking for whether the user has clicked on any part of the slider
    if(focussed(this.position.x, this.position.y, this.sliderWidth, this.sliderHeight) && mousePressed)
    {
     this.ballX = mouseX;  
    }
    //Checking for whether the user is dragging the ball. 
    if(focussed(this.ballX - this.ballRadius, this.ballY - this.ballRadius, this.ballRadius*2, this.ballRadius*2) && mousePressed)
    {
      if(mouseX > this.position.x && mouseX < this.position.x + this.sliderWidth)
      {
        this.ballX = mouseX; 
      }
    }
    
    //Drawing the body rectangle. 
    fill(255, 255, 255); 
    rect(this.position.x, this.position.y, this.sliderWidth, this.sliderHeight, this.bavel); 
    
    //Drawing the filled porition
    fill(this.sliderColor); 
    float fillWidth = this.ballX - this.position.x; 
    rect(this.position.x, this.position.y, fillWidth, this.sliderHeight, this.bavel); 
    
    //Drawing the ball. 
    fill(255, 255, 255); 
    ellipse(this.ballX, this.ballY , this.ballRadius, this.ballRadius); 
  }
  
}; 
