#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);
#include "bitmap.h"
#define select 10
#define back 2
#define LED1 5
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
int frame = 0;

void setup() {
  Serial.begin(9600);
  display.begin(0x02, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  pinMode(select, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  intro();
  byte r = push(select);
  if (r) {
    Serial.println(r);
    if (r == 1) {
      byte p = panel();
      if (p == 1) digitalWrite(LED1, HIGH);
      else if (p == 2) digitalWrite(LED1, LOW);
    }
  }
}
