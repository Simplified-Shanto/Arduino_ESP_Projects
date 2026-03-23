#include <Adafruit_SSD1306.h> 
Adafruit_SSD1306 display(128, 64, &Wire, -1); 
#include "bitmap.h"
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]));  
int frame = 0; //Starting with the very first frame. 
#define select 10 //button for selecting item in the list
#define back 2 //Button for getting back from the menu
#define LED1 5
#define LED2 4
#define LED3 3


void setup() {
 Serial.begin(9600); 
 display.begin(0x02, 0x3C); 
 display.clearDisplay(); 
 display.setTextSize(2); 

  pinMode(select, INPUT_PULLUP); 
  pinMode(back, INPUT_PULLUP); 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
}

void loop() {
  intro(); //Intro will keep running unless we press anything 
  byte r = push(select); //Outputs 0, 1, 2 based on the type of press 
                         //detected
  if(r)
  {
    Serial.println(r); 
    if(r==1) 
    {
      byte p = panel(); 
      if(p==1) digitalWrite(LED1, HIGH); 
      if(p==2) digitalWrite(LED1, LOW); 
      if(p==3) digitalWrite(LED2, HIGH); 
      if(p==4) digitalWrite(LED2, LOW); 
      if(p==5) digitalWrite(LED3, HIGH); 
      if(p==6) digitalWrite(LED3, LOW); 
    }
  }
 
 
}
