float[][] distances;
float maxDistance;
float spacer;

void setup()
{
  size(640, 360);
  maxDistance = dist(width/2, height/2, width, height);
  distances = new float[width][height];
  for(int i = 0; i<100; i++)
  {
      for(int j = 0; j<100; i++)
        {
          distances[i][j] = dist(width/2, height/2, i, j)/maxDistance;
        }
  }
  spacer = 7;
  strokeWeight(5);
  background(255, 255, 255);
  noLoop();
}

void draw()
{
  
  for(int i = 0; i<100; i+=spacer)
  {
    for(int j = 0; j<100; j+=spacer)
    {
      stroke(distances[i][j]*255);
   // stroke(random(30, 200)); 
      point(spacer/2 + i, spacer/2 + j);
    }
  }
  
  
}
