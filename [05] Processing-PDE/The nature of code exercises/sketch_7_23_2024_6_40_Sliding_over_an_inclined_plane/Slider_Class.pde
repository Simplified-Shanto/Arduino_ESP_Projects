boolean focussed(float x, float y, float l, float b)
{
  
  if(  (mouseX > x && mouseX< x + l ) && (mouseY > y  && mouseY < y + b)  )
  {
    return true; 
  }
  return false; 
}

class Slider{
  PVector position; 
  float sliderHeight; 
  float sliderWidth; 
  float sliderValue; 
  float startValue; 
  float endValue; 
  color sliderColor; 
  float bavel;  
  float ballX; 
  float ballRadius; 
  float ballY;
  String sliderLabel; 
  String sliderValueUnit; 
  
  
  
  Slider(float x, float y, float sv , float ev, String lb)
  {
    position = new PVector(x, y); 
    startValue = sv; 
    endValue = ev; 
    sliderLabel = lb; 
    
    
    bavel = 90; 
    sliderWidth = 200; 
    sliderHeight = 15; 
    sliderColor = color(0, 150, 200);  
    ballX = x + sliderWidth/4.0; 
    ballY = y + sliderHeight/2.0; 
    ballRadius = 1.5*sliderHeight;
    
  }
  
  void drawSlider()
  {
   //Rendering Slider value. 
   this.sliderValue = ((this.ballX - this.position.x)/this.sliderWidth);
   this.sliderValue = map(this.ballX - this.position.x, 0, this.sliderWidth, this.startValue, this.endValue); 
   
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
    strokeWeight(0.5); 
    stroke(0, 0, 0); 
    fill(255, 255, 255); 
    rect(this.position.x, this.position.y, this.sliderWidth, this.sliderHeight, this.bavel); 
    
    //Drawing the filled porition
    fill(this.sliderColor); 
    float fillWidth = this.ballX - this.position.x; 
    rect(this.position.x, this.position.y, fillWidth, this.sliderHeight, this.bavel); 
    
    //Drawing the ball. 
    fill(220, 220, 255); 
    ellipse(this.ballX, this.ballY , this.ballRadius, this.ballRadius); 
    
    
    textSize(25); 
    fill(0, 5 , 20) ; 
    //Drawing the label of the slider. 
    float heightOffset = 18; 
    float textPosition = this.position.x + this.sliderWidth + 15 ; //Having an space of 20 pixel from the slider. 
    text(this.sliderLabel,textPosition , this.position.y + heightOffset);
    //Drawing the value from the slider. 
    float labelLength = this.sliderLabel.length(); 
    labelLength = (1.0 - labelLength/100.0)*15*labelLength; //Here we assume that the maximum length of the lable will be 100 characters. 
    //and make some rough adjustments to remove the irregularlity in the horizontal widht of different letters. 
    //Larger the length of the label, some amount of offset will be deducted. 
    textPosition+=labelLength; //Considering each character of the label will occupy 10 pixel horizontally. 
    text(this.sliderValue, textPosition , this.position.y + heightOffset); 
    //Drawing the unit. 
    
  }
  
}; 
