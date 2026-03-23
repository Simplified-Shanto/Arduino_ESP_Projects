

void setup()
{
  size(800, 800);
  

 pushMatrix();
    translate(400, 400);
    
    float rad1 = 600;
    stroke(0, 0, 0);
    strokeWeight(1);
ellipse(0,0, rad1, rad1);

    float rad2 = 273;
    ellipse(0, 0, rad2, rad2);
    
   
    
    float rad4 = 249;
     strokeWeight(2);
    stroke(156, 156, 156);
    ellipse(0, 0, rad4, rad4);
    
     float rad3 = 109;
    ellipse(0, 0, rad3, rad3);
    
    
for(int i = 0; i<360; i+=20)
{

    rotate(20);
     stroke(0, 0, 0);
    strokeWeight(1);
    line(0, 0, 300, 0);
    fill(0, 0, 0);
    text(i+10, 142, 4);
    line(166, 0, 175, 0);
    
  
}

  popMatrix();

}





   
