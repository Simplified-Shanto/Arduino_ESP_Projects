PImage groupImage;

void setup(){
size(1000, 500);
groupImage = loadImage("Khan Academy Logo.png");

}

void draw()
{
  background((millis()/30)%250, (millis()/20)%250, (millis()/10)%250);
 image(groupImage, 50, 170, 900, 150); 
}
