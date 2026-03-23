float amplitude = 30; 
float waveY = 200; 

void setup()
{
 size(1000, 800); 
 
 background(255); 

 // frameRate(1); 
}

int start = 0; 
int counter = 0; 

void draw()
{
  background(255); 
 
   stroke(0, 100, 255); 
 strokeWeight(2); 
 for(int i = start; i<=1000; i+=amplitude, counter++)
 {
   if(counter%2==1) { 
   line(i, waveY, i+amplitude, waveY); 
   
   }
   else
   {
     line(i, waveY - amplitude, i+amplitude, waveY - amplitude);
   }
   line(i+amplitude, waveY, i+amplitude, waveY - amplitude); 
 }
 
 start--; 
 
}
