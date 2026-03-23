#include <Arduino.h>

void setup() {
  Serial.begin(115200); 
  digitalWrite(4, HIGH); 
  delay(1000); 
  digitalWrite(4, LOW); 

 
delay(250);
// Setup WiiMote
if (psramInit())
printf("PSRAM init OK\n");
printf("PSRAM size: %d\n", ESP.getFreePsram());

  
  Serial.print("Total heap: %d");
  Serial.println(ESP.getHeapSize()); 
  Serial.print("Free heap: %d");
  Serial.println(ESP.getFreeHeap()); 
  Serial.print("Total PSRAM: %d"); 
  Serial.println( ESP.getPsramSize());
  Serial.print("Free PSRAM: %d"); 
  Serial.println(ESP.getFreePsram());

  delay(1000);  
  digitalWrite(4, HIGH); 
  delay(1000); 
  digitalWrite(4, LOW); 
}

void loop() {}
