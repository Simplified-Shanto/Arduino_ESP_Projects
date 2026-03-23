#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float current;
float voltage;



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
  display.println("Current");
  display.display();

  // Initialize servos
  // servo1.attach(pwmPins[0]);
  // servo2.attach(pwmPins[1]);
  // servo3.attach(pwmPins[2]);
  // servo4.attach(pwmPins[3]);
}

void loop() {
  // Read analog inputs and map to servo angles
  // int angles[4];
  // for (int i = 0; i < 4; i++) {
  //   int analogValue = analogRead(analogPins[i]);
  //   angles[i] = map(analogValue, 0, 1023, 0, 180);
  // }

  // Set servo positions
  // servo1.write(angles[0]);
  // servo2.write(angles[1]);
  // servo3.write(angles[2]);
  // servo4.write(angles[3]);
  int adc = analogRead(A0);
  float voltage = adc * 5.0 / 1023.0;
  float current = (voltage-2.5) / 0.185;
  if(current<0.16){
    current = 0;
  }


  // Update OLED display with servo angles
  display.clearDisplay();
  display.setTextSize(1);
 // display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Current:");
  display.println(current);
  display.print("Analog Reading:");
  display.println(adc);
  display.print("Voltage: ");
  display.println(voltage);
  // display.print("Servo 4: ");
  // display.println(angles[3]);
  display.display();

  delay(500); // Adjust delay as needed for smoother display updating
}
