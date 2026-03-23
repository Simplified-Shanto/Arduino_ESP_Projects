#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <MQUnifiedsensor.h>
#include <string.h>
#include <iostream> 
//#include <sstream> 


#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C

#define DHTPIN A3   // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;



/************************Hardware Related MQ4 Macros************************************/
#define         Board                   ("Arduino Nano")
#define         Pin                     (A2)  //Analog input 4 of your arduino
/***********************Software Related MQ4 Macros************************************/
#define         Type                    ("MQ-4") //MQ4
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ4CleanAir        (4.4) //RS / R0 = 60 ppm 
/*****************************Globals***********************************************/
//Declare Sensor
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

   bmp.begin(); 
     /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

                    //Set math model to calculate the PPM concentration and the value of constants
  MQ4.setRegressionMethod(0); //_PPM =  pow(10, (log10(ratio)-b)/a)
  MQ4.init(); 
  //MQ-4 calibration
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
  }
  MQ4.setR0(calcR0/10);
  //MQ-4 calibration error warnings. 
   if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); }
  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); }

}


void loop() {
  // Delay between measurements.
  delay(3000);

  // Get temperature event and print its value.
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("DHT22 Temperature: Error"));
  }
  else {
    Serial.print(F("DHT22 Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }


  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("DHT22 Humidity: Error"));
  }
  else {
    Serial.print(F("DHT22 Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

   Serial.print(F("BMP280 Temperature: "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

  
    Serial.print(F("BMP280 Pressure: "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");


    //MQ4 reading part. 
    MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ4.setA(-0.318); MQ4.setB(1.133); // A -> Slope, B -> Intersect with X - Axis
    float LPG = MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

     //  exposure to 2000 ppm of LPG gas is immediately dangerous to life and health. In this section
    if(LPG>=2000) 
    {
      Serial.print("MQ4 LPG level: (!)"); 
      Serial.print(LPG); 
      Serial.println("ppm"); 
    }
    else 
    {
       Serial.print("MQ4 LPG level: "); 
      Serial.print(LPG); 
      Serial.println("ppm"); 
    }
      
    

}
