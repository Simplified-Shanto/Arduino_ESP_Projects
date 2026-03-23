import processing.serial.*; 

void drawRadar(float angle, float distance)
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
  
  pushMatrix();
  rotate(radians(-angle)); 
  strokeWeight(3); 
  stroke(66, 123, 245); 
  distance = constrain(distance, 0, 1480); 
  line(0, 0, distance*10, 0); 
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


String portname = Serial.list()[0]; 
Serial port = new Serial(this, "COM3", 9600); 
 
void setup()
{
 size(1600, 900);  
  
}

float Angle = 0; 
int inc = 1; 
int dec = 0; 

String ang = ""; 
String distance = "hat"; 
String reading = ""; 
int index = 0; 
float angle = 0; 
float Distance = 0; 


void draw()
{
  background(0); 
  
  fill(3, 148, 252); 
  if(port.available()> 0)
  {
   reading = port.readStringUntil('.');
   index = reading.indexOf(','); 
   ang = reading.substring(0, index); 
   distance = reading.substring(index+1, reading.length()-1); 
  }
  
 angle = float(ang); 
 Distance = int(distance); 
 
    drawRadar(angle, Distance); 
    
}
