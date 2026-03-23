// defines pins numbers
const int potPin = A0;
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 2;
const int buttonPin = 12;

// defines variables
long duration;
int distance;
int safetyDistance;
int limit;    // Limiting value for triggering the buzzer
int disFeet;  //variable to store distance in feet
int del;  //Relative delay within the selected range

void beep(int del)    //Function for beeping when safe distance is crossed
{
   digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(del);
   digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  delay(del);
  
}

void countDistance(int n) 
{
  for(int i = 1; i<=n; i++)
  {
    digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
    delay(300);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  delay(300);
  }
}
void setup() {
    pinMode(potPin, INPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(buzzer, OUTPUT); //Sets buzzer Pin as an Output
    pinMode(ledPin, OUTPUT);  //Sets LED pin as an Output
    Serial.begin(9600); // Starts the serial communication
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

          // Sets the trigPin on HIGH state for 10 micro seconds
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          
          // Reads the echoPin, returns the sound wave travel time in microseconds
          duration = pulseIn(echoPin, HIGH);
          
          // Calculating the distance
          distance= duration*0.034/2;

  int value = analogRead(A0);
  limit = map(value, 0, 1023, 5, 100);


if (distance <= limit){
  if(distance<=10)
  {
   digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
  }
  else
  {
   del = map(distance, 0, limit, 20, 300);
  beep(del);
  }
}
else 
{
   digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
}


// Prints the distance on the Serial Monitor

if(digitalRead(buttonPin)!=0)
{
  delay(300);
  disFeet = (distance+29)/30;
  if(disFeet<=20)
  {
  countDistance(disFeet);
  }
}

//Serial.print("Feet: ");
//Serial.println(disFeet);
}
