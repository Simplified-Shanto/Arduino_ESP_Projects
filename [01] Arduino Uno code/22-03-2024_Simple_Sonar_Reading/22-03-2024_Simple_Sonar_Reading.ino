
#define frontSonarTrig 3
#define frontSonarEcho 2

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  Serial.begin(9600); 
  pinMode(frontSonarTrig, OUTPUT); 
  pinMode(frontSonarEcho, INPUT); 
  // put your main code here, to run repeatedly:
  Serial.println(frontDistance()); 
  delay(500); 

}


int frontDistance()
{
  digitalWrite(frontSonarTrig, LOW); //Extra pin number 14
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(frontSonarTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(frontSonarTrig, LOW);
 long duration = pulseIn(frontSonarEcho, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  return duration*0.0068; //returns distance in inch. 
}
