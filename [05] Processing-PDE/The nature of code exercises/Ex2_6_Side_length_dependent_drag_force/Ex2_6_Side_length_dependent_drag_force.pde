Mover[] movers = new Mover[20];

//Objective: To check the behaviour of moving objects in a medium having drag force; liquid. 
//Challenge: Can one object of a class access the methods and attributes of another object of the same class? 
//I mean can we anyhow prevent those stones from overlapping on to each other, by applying some sort 
//of checkEdge() function? 
//Well, we may try the approach by checking manually, for n movers, we'll have to check n*(n-1) times
// Better if we can try it with exercise 2.6. 
Liquid waterTub; 



void setup() {
  size(1000, 800);
  smooth();
  background(255);
   waterTub = new Liquid(0, height/2, width, height/2, 0.1); 
  for (int i = 0; i < movers.length; i++)
  {
    movers[i] = new Mover(random(0.1, 5),random(15, 70),  random(0, width), random(0, height/2-100));
  }
}




void draw()
{
  background(255);
  

  for (int i = 0; i < movers.length; i++)
  {
    float m = movers[i].mass;
    PVector wind = new PVector(0.01, 0);
    PVector gravity = new PVector(0, 0.1*m);

    PVector friction = movers[i].velocity.get(); //We want the velocity to be intact, so just making a copy
    friction.normalize(); //Friction is not directly proportional to the velocity.
    friction.mult(-1);   //Friction acts in the opposite direction to the velocity.
    float c = 0.01;       //Coefficient of friction.
    friction.mult(c);
    
    if(movers[i].isInsideLiquid(waterTub)) //Drag force only acts in the liquid part. 
    {
      movers[i].drag(waterTub); 
    }
    else
    {   
    movers[i].applyForce(friction); //Friction force of air molecule. Only active when in the air. 
    movers[i].applyForce(wind);     //Only active when the objects are in the air. 
    }

    movers[i].applyForce(gravity);  //Gravitaional force, always active along with other force. 
    movers[i].update();
    movers[i].checkEdges();
    movers[i].display();
  }
  waterTub.drawLiquid(); 
}
