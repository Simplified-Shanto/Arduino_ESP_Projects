float wavePoints = 250; 
float amplitude = 30;
float radius = 10; 
float xPos = 20; 

Slider amplitudeSlider = new Slider(20, 30, 250, 20, color(40, 150, 200)); 
Slider wavePointsSlider = new Slider(20, 80, 250, 20, color(200, 40, 200)); 
Slider radiusSlider = new Slider(20, 130, 250, 20, color(40, 200, 150)); 


void setup()
{
  size(1000, 800); 
  
}


void draw()
{
  background(255, 255, 255); 
 
  
  textSize(40); 
  //stroke(0, 200, 150); 
  text("Amplitude = ", 300, 50); 
  text(round(amplitude), 520, 50); 
  text("WavePoints = ", 300, 100); 
  text(round(wavePoints), 530, 100); 
  text("Radius = ", 300, 150); 
  text(round(radius), 480, 150); 
  
   amplitudeSlider.drawSlider(); 
  wavePointsSlider.drawSlider(); 
  radiusSlider.drawSlider(); 
  
  amplitude  =  2*amplitudeSlider.sliderValue; 
  wavePoints = 2*wavePointsSlider.sliderValue; 
  radius     =    radiusSlider.sliderValue; 

  
  
  
  
  
  
  
  float initialPhase = frameCount; 
  for(int i = 1; i<=wavePoints; i++)
  {
   
    float displacement =  width/2 + amplitude*sin(radians(initialPhase + xPos)); 
    fill(20, 150, 200); 
    noStroke(); 
    rect(xPos - radius/2.0-1, displacement, radius +1, height - displacement); 
    strokeWeight(0.5); 
     fill(0, 200, 220); 
    ellipse(xPos,displacement , radius, radius); 
    
   
  
    xPos+=radius; 
    
  }
  xPos = radius; 
  
}
