class Toggle
{
  PVector position; 
  float size = 0; 
  color onColor = color(63, 161, 232);
  color offColor = color(255, 255, 255);
  float scale = 2; 
  int state = 1;  
  float radius = 20; 
  
  Toggle(float x, float y)
  {
    position = new PVector(x, y); 
  }
  
  void drawToggle()
  {
    noStroke(); 
    float Length = 50*scale; 
    float Breadth = 25*scale; 
    float Bavel = 25*scale; 
    
    if(focussed(position.x, position.y, Length, Breadth) && mousePressed)
    {
       state = 1 - state;  
       delay(200); 
    }
    
    
    float Radius = Breadth - 7.0*scale; 
    if(state==0)
    {
    fill(offColor); 
   rect(this.position.x, this.position.y, Length, Breadth,  Bavel );
   fill(onColor); 
   ellipse(position.x + Length/4.0, position.y + Breadth/2.0 , Radius, Radius); 
    }
    else
    {
     fill(onColor); 
     rect(position.x, position.y, Length, Breadth, Bavel); 
     fill(offColor); 
     ellipse(position.x + Length*0.75, position.y + Breadth*0.5, Radius, Radius); 
    }
    
    
  }
  
  
}; 


boolean focussed(float x, float y, float l, float b)
{
  
  if(  (mouseX > x && mouseX< x + l ) && (mouseY > y  && mouseY < y + b)  )
  {
    return true; 
  }
  return false; 
}
