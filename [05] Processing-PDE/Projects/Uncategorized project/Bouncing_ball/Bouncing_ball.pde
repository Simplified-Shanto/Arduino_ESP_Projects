
void setup()
{
  size(400, 400);
}

float t = 0;
float y = 0;

void draw (){
  noStroke();
    background(186, 255, 232);
    fill(255, 255, 255);
    rect(0, 250, 400, 150);
    
    y = -0.02*t*t + 3.5*t;
    
    float grey = 0.1 * y + 200;
    float shadowSize = 0.2 * y + 50;
    fill(grey, grey, grey);
    ellipse(200, 300, shadowSize, 10);
    
    float correctedY = 250 - y;

    fill(71, 117, 255);
    ellipse(200, correctedY, 50, 50);

    if (y < 0) {
        t = 0;
    }
    
    t += 5;
}
