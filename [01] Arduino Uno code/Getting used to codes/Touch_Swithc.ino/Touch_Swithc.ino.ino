#include<CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(4,2);

int threshold = 1000;
  const int led = 12;
 
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


int state = 1;
void loop() {
  long sensorValue = capSensor.capacitiveSensor(30);
  Serial.println(sensorValue);

  if(sensorValue > threshold) {
    delay(250);
   state++;
  }
  if(state%2==0){
   digitalWrite(led,HIGH );
  }
  else{
  digitalWrite(led, LOW);
  delay(50);
  }
}
