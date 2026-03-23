class Stick{
  float x;
  float y;
  
  Stick(float X, float Y)
  {
    x = X;
    y = Y;
  }
  void drawStick(){
   rectMode(CENTER);
   fill(156, 144, 130);
   rect(x, y, 5, 40);
  }
  
}
