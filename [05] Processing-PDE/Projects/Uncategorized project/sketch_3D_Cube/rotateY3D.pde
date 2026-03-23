void rotateY3D(float theta)
{
  float sinTheta = sin(theta);
  float cosTheta = cos(theta);
  for(int n = 0; n<nodes.length; n++)
  {
    float x = nodes[n][0];
    float z = nodes[n][2];
    nodes[n][0] = x * cosTheta + z * sinTheta;
    nodes[n][2] = z * cosTheta - x * sinTheta;
  }
}
