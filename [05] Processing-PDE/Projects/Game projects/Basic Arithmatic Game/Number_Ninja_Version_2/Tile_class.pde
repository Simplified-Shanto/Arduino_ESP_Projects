class Tile{
  PVector Position; 
  float Length = 93; 
  float Breadth = 48; 
  float Bavel = 4; 
  String value = ""; 
  color Color = color(0, 157, 255); 
  color focussedColor= color(83, 183, 194); 
  color wrongColor = color(245, 68, 68); 
  color correctColor = color(149, 237, 7); 
  color activeColor = Color; 
  float txtSize = 40; 
  color txtColor = color(255, 255, 255); 
  
  
  //Constructor
  Tile(String s, float x, float y)
  {
    Position = new PVector(x, y); 
    value = s; 
  }
  //Selection method
  int select()
  {
   if(isFocussed(Position.x, Position.x + Length, Position.y , Position.y + Breadth))
   {
     activeColor = focussedColor; 
      if(mousePressed) 
        {
            return 1; 
        }
        else {
            
            return 0;
        }
   }
   else
   {
    activeColor = Color; 
    return 0; 
   }
  }
  
    void drawTile()
    {
     fill(activeColor); 
     
     noStroke(); 
     rect(Position.x, Position.y, Length, Breadth, Bavel); 
     float tpX = 30; 
     var tpY = 38; 
     
     textSize(txtSize); 
     fill(txtColor); 
     text(value, Position.x + tpX, Position.y + tpY); 
     
      
    }


 
};



boolean isFocussed(float xa, float xe, float ya, float ye)
{
    if(mouseX > xa && mouseX < xe && mouseY > ya && mouseY < ye)
    {
     return true;    
    }
    else 
    {
      return false;   
    }
}
