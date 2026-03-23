Mover[] movers = new Mover[20];
attractor[] attractors = new attractor[5];

//Objective: To check the behaviour of moving objects in a medium having drag force; liquid.
//Challenge: Can one object of a class access the methods and attributes of another object of the same class?
//I mean can we anyhow prevent those stones from overlapping on to each other, by applying some sort
//of checkEdge() function?
//Well, we may try the approach by checking manually, for n movers, we'll have to check n*(n-1) times
// Better if we can try it with exercise 2.6.


void setup() {
  size(1000, 800);
  smooth();
  background(255);

  for (int i = 0; i<attractors.length; i++)
  {
    attractors[i] = new attractor();
  }
  for (int i = 0; i < movers.length; i++)
  {
    movers[i] = new Mover(random(30, 50), random(50, width-50), random(50, height));
  }
}




void draw()
{
  background(255);


  for (int i = 0; i < movers.length; i++)
  {
    for (int j = 0; j< movers.length; j++)
    {
      if (j<attractors.length)  //Force applied by attractor
      {
        PVector gravitationalPull = attractors[j].attract(movers[i]);
        movers[i].applyForce(gravitationalPull);
        attractors[j].drawAttractor();
      }
      if (i!=j)
      {
        PVector selfAttraction = movers[i].attract(movers[j]);
        movers[i].applyForce(selfAttraction);
      }
    }
    movers[i].update();
    movers[i].checkEdges();
    movers[i].display();
  }
}
