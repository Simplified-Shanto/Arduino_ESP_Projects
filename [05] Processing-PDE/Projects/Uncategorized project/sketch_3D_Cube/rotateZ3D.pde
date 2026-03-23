void rotateZ3D(float theta)
{
  float sinTheta = sin(theta);
  float cosTheta = cos(theta);
  for(int n = 0; n<nodes.length; n++)
  {
    float[] node = nodes[n];
    float x = node[0];
    float y = node[1];
    nodes[n][0] = x * cosTheta - y * sinTheta;
    nodes[n][1] = y * cosTheta + x * sinTheta;
  }
}
