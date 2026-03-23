void setup()
{
  size(600, 400); 
}

char c = char(round(random(97, 122))); 
String tst = "test"; 

int wrong = 0; 
int lastPress = millis(); 
int wrongPress = 0; 
int rightPress = 0; 
int minute = 0; 
int second = 0; 

color letterColor = color(0, 0, 0); 
color wrongLetter = color(242, 19, 79); 
color letterFill = letterColor; 

void draw() {
   background(255); 
   second = round(millis()/1000)%60; 
   minute = round(millis()/60000); 
 
  textSize(90); 
  fill(letterFill); 
  text(c , 300, 300); 
  
  
if(millis() - lastPress > 150 && keyPressed)
{
 if(key==c)
 {
  c = char(round(random(97, 122))); 
  rightPress++; 
  letterFill = letterColor; 
 }
 else
 {
   wrongPress++; 
   letterFill = wrongLetter; 
 }
 
  lastPress = millis(); 
}

    textSize(50); 
    fill(137, 235, 52); 
   text("Right  = ", 20, 50); 
   text(rightPress, 350, 50); 
   
    fill(252, 155, 43); 
   text("Wrong press = ", 20, 100); 
   text(wrongPress, 350, 100); 
   
    fill(10, 182, 250); 
   text("Time : ", 20, 150); 
   text(second, 350, 150); 
   text(':',340, 150); 
   text(minute, 290, 150); 

}
