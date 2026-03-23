
import processing.serial.*; 


String portName = Serial.list()[0]; 
Serial port = new Serial(this, portName, 9600); 

Point A; 
color Orange = color(200, 50, 50); 
int xPos; 
int yPos = 50; 

PVector velocity; 
PVector acceleration; 


void setup()
{
  size(800, 800); 
   A = new Point(200.0, 300.0,20, Orange);
   velocity  = new PVector(0, 0); 
   acceleration = new PVector(0, 0); 
  
}

String data = "", xVal = "" , yVal = ""; 
int index1; 


void draw() 
{
 background(138, 235, 12);

 
 if(port.available()> 0)
 {
  data = port.readStringUntil('\n');
  index1 = data.indexOf(','); 
  xVal = data.substring(0, index1); 
  yVal = data.substring(index1 + 1 , data.length() -1 ); 
  
  xPos = int(xVal); 
  yPos = int(yVal); 
 }
 
 textSize(40); 
   fill(54, 94, 168);
 text("xPos = ", 20, 30);
 text(xPos, 200, 30); 
 text("yPos = ", 20, 70); 
 text(yPos, 200, 70); 
 
 
 velocity.x = xPos - 520; 
 velocity.y = yPos - 500; 
 velocity.x/=80.00;
 velocity.y/=80.00; 
 
A.Position.x = constrain(A.Position.x, 10, width - 10); 
A.Position.y = constrain(A.Position.y, 10, height-10); 
 
 
 A.Position.add(velocity); 
 
 
 
 textSize(40); 
 fill(54, 94, 168); 
 text("xVelocity = ", 300, 30);
 text(velocity.x, 500, 30); 
 text("yVelocity  = ", 300, 70); 
 text(velocity.y, 500, 70); 
 
 
 if(mousePressed)
 {
  A.Position.x = mouseX; 
  A.Position.y = mouseY; 
 }
 
 
  A.drawPoint(); 
  
}
