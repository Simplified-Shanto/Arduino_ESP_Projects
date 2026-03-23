import processing.serial.*; 

String portName = Serial.list()[1]; 
Serial port = new Serial(this, "COM3", 9600); 

void setup()
{
 size(400, 400); 
 
}
String data = "", L1 = "", L2 ="", L3 = "", L4=""; 
int index1, index2, index3; //To store indices of
                             //of ,.and- of in the
                             //coming message from
                             // the port. 
String fata = ""; 
void draw()
{
 background(255); 
 stroke(0); 
 strokeWeight(2); 
 line(width/2, 0, width/2, height); //Vertical line
 line(0, height/2, width, height/2); //Horizontal line
 
 if(port.available()>0)
 {
   // println(port.available()); 
  data = port.readStringUntil('\n');
  if(data!=null)
  {
  index1 = data.indexOf(','); 
  index2 = data.indexOf('.'); 
  index3 = data.indexOf('-'); 
  L1 = data.substring(0, index1); 
  L2 = data.substring(index1+1, index2); 
  L3 = data.substring(index2+1, index3); 
  L4 = data.substring(index3+1, data.length()); 
  
  fill(0); 
  textSize(20); 
  text(L1, (width/4)*3, height/4); 
  text(L2, width/4, height/4); 
  text(L3, width/4, (height/4)*3); 
  text(L4, (width/4)*3, (height/4)*3); 
  }
  
  
  }
 
 
  fill(0); 
  textSize(20); 
  text(L1, (width/4)*3, height/4); 
  text(L2, width/4, height/4); 
  text(L3, width/4, (height/4)*3); 
  text(L4, (width/4)*3, (height/4)*3); 
}
