#include <EEPROM.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire display;

#define select 10
#define back 2
#define LED1 3
#define LED2 5
#define LED3 8

bool led1_state, led2_state, led3_state, led2p = 0;
byte led2_brightness;
byte led1_blink_time, led2_blink_time;
uint32_t l1, l2;

int led2b = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000L);
  display.begin(&Adafruit128x64, 0x3C);
  // display.clearDisplay();
  display.setFont(System5x7);
  display.set2X();

  pinMode(select, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(13, OUTPUT);
  memory_read();
  intro();
}

void loop() {
  byte r = push(select);
  if (r) {
    digitalWrite(LED1, 0);
    analogWrite(LED2, 0);
    digitalWrite(LED3, 0);

    if (r == 1) {
      byte p = panel();
      if (p == 1) LED_control();
    }
    intro();
  }

  digitalWrite(LED3, led3_state);
  if (led1_state) {
    if (millis() - l1 > led1_blink_time * 10) {
      l1 = millis();
      digitalWrite(LED1, !digitalRead(LED1));
    }
  } else digitalWrite(LED1, 0);

  if (led2_state) {
    if (millis() - l2 > ((led2_blink_time * 10) / led2_brightness)) {
      l2 = millis();
      (led2p == 0) ? led2b++ : led2b--;
      if (led2b == led2_brightness) led2p = 1;
      if (led2b == 0) led2p = 0;
      analogWrite(LED2, led2b * 2.5);
    }
  } else analogWrite(LED2, 0);
}
