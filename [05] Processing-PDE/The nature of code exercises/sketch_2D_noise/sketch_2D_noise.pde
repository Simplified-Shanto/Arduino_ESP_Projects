float change = 0.0001; 
int incre = 1; 
void setup()
{
 size(1000, 800); 
frameRate(60); 
 
}

void draw()
{

   loadPixels();
float xoff = 0.0;
for (int x = 0; x < width; x++) {
//For every xoff, start yoff at 0. 
float yoff = 0.0;
for (int y = 0; y < height; y++) {
//Use xoff and yoff for noise().
float bright = map(noise(xoff,yoff),0,1,0,255);
//Use x and y for pixel location.
pixels[x+y*width] = color(0, bright, 255);
//Increment yoff. 
yoff += change; }
//Increment xoff. 
xoff += change; }
updatePixels();

if(change > 0.01) { incre = 0;    }
if(change < 0.0001) { incre = 1; }

if(incre==0) { change-=0.0001; }
else { change+=0.0001; }


}
