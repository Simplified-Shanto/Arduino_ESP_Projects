#include <DHT11.h>

DHT11 dht11(32);
unsigned long lastReading = 0;

#define soilSensorPin 35
#define gasSensorPin 34

byte showTemperature() {

  buttonPressed = false;
  while (1) {
    if (millis() - lastReading > 1200) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Temperature:   ");
      display.print(dht11.readTemperature());
      display.println(" *C"); 
      display.setCursor(0, 10);
      display.print("Humidity:      ");
      display.print(dht11.readHumidity());
      display.println(" %"); 
      display.setCursor(0, 20);
      display.print("Soil moisture: ");
      display.println(analogRead(soilSensorPin));
      display.setCursor(0, 30);
      display.print("Gas reading  : ");
      display.println(analogRead(gasSensorPin));


      display.display();
      lastReading = millis(); 
    }


    if (buttonPressed == true) {
      delay(200);
      buttonPressed = false;
      return 0;
    }
  }
}