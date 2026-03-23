
void setup()
{
  size(800, 800);
}

void draw()
{
   background(255,255,255);
int Blue = color(74, 70, 87);
int pink = color(224, 9, 159);

stroke(247, 15, 173);
line(52,0,52,width);
line(49,0,49,width);

int lineSpace = 11;
for(int y = 50; y<=width;y+=55)
{
 
   stroke(247, 15, 173);
   line(0,y,width,y);
   stroke(Blue);
   line(0,y+lineSpace,width,y+lineSpace);
   line(0,y+lineSpace*2,width,y+lineSpace*2);
   stroke(pink);
   line(0,y+lineSpace*3,width,y+lineSpace*3);
}
}
