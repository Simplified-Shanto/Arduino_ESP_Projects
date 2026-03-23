class Point {
  PVector Position = new PVector(width/2, height/2);  //the position of the point
  float Radius;  //The radius of the point while not on focus. 
  float drawingRadius; //The active radius. For both focussed and unfocussed. 
  float offset = 20.0 ; 
  color pointColor = color(255, 149, 0); //Colour of the point. 
  int isFocussed = 0; //Whether the point is in focus. 
  
  
  //Constructor. 
  Point(float xpos, float ypos, float rad, color col)
 {
   this.pointColor = col; 
   this.Position.x = xpos; 
   this.Position.y = ypos; 
   Radius = rad; 
   offset+=Radius; 
  
  }
  //Methods
  void drawPoint()
  {
     if(mouseX > this.Position.x - this.Radius && mouseX <this.Position.x + this.Radius
   && mouseY > this.Position.y - this.Radius && mouseY < this.Position.y + this.Radius) 
    {
      this.isFocussed = 1; 
        this.drawingRadius = this.offset; 
        if(mousePressed)
        {
            this.Position.x  = mouseX; 
            this.Position.y  = mouseY; 
        }
    }  else { this.drawingRadius = this.Radius;  this.isFocussed = 0;  }
    
    noStroke(); 
    fill(pointColor);
    ellipse(this.Position.x, this.Position.y, this.drawingRadius, this.drawingRadius); 
  }
}; 
