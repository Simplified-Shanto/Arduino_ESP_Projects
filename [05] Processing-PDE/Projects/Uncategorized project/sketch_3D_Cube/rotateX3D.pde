void rotateX3D(float theta)
{
  float sinTheta = sin(theta);
  float cosTheta = cos(theta);
  for(int n = 0; n<nodes.length; n++)
  {
    float y = nodes[n][1];
    float z = nodes[n][2];
    nodes[n][1] = y * cosTheta - z * sinTheta;
    nodes[n][2] = z * cosTheta + y * sinTheta;
  }
}
