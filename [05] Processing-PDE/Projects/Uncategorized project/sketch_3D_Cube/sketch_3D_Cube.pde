color backgroundColor = color(255);
color nodeColor = color(40, 168, 107);
color edgeColor = color(34, 68, 204);
int nodeSize = 20;
int side = 200;
                 
void setup()
{
  size(1200, 800);
 rotateZ3D(60);
rotateY3D(60);
rotateX3D(60);
}

void draw()
{
  background(backgroundColor);
  pushMatrix();
  translate(600, 400);
  stroke(edgeColor);
  strokeWeight(3);
 
      for(int e = 0; e<edges.length; e++)
      {
         int n0 = edges[e][0];
         int n1 = edges[e][1];
         float[] node0 = nodes[n0];
         float[] node1 = nodes[n1];
         line(node0[0], node0[1], node1[0], node1[1]);
      }
      
      //Drawing nodes
      fill(nodeColor);
      noStroke();
      for(int n = 0; n<nodes.length; n++)
      {
        ellipse(nodes[n][0], nodes[n][1], nodeSize, nodeSize);
      }
  popMatrix();
  
}
