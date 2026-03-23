
int pins[8] = {2, 3, 4, 6, 7, 8};
int pinSize = 6;
int Delay = 50;

void setup()
{
  for(int i = 0; i<pinSize; i++)
  {
    pinMode(pins[i], OUTPUT);
  }
}



void loop() 
{
 for(int i = 0; i<pinSize; i++)
 {
  digitalWrite(pins[i], HIGH);
  delay(Delay);
  digitalWrite(pins[i], LOW);
  delay(Delay);
 }
}
