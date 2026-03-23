#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int analogPins[4] = {A0, A1, A2, A3};
const int pwmPins[4] = {3, 5, 6, 9};

#define RCPin 2
volatile long StartTime = 0;
volatile long CurrentTime = 0;
volatile long Pulses = 0;
int PulseWidth = 0;


void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hi!");
  display.display();

  // Initialize servos
  servo1.attach(pwmPins[0]);
  servo2.attach(pwmPins[1]);
  servo3.attach(pwmPins[2]);
  servo4.attach(pwmPins[3]);

   pinMode(RCPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RCPin), PulseTimer, CHANGE);

  
}

void loop() {
 if(Serial.available())
 {
  String message = Serial.readStringUntil('.'); 
  display.clearDisplay(); 
  display.println(message); 
  display.display(); 
 }
}


void PulseTimer(){
  CurrentTime = micros();
  if(CurrentTime > StartTime)
  {
    Pulses = CurrentTime - StartTime; 
    StartTime = CurrentTime; 
  }
}