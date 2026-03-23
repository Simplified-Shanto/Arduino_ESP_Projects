

#define R1 10000.00  //10K ohm
#define R2 2000.00   //2K ohm
#define voltageSensorPin  A4

float voltageReading()
{

   // float VIN = map(analogRead(voltageSensorPin), 0.0, 1023.0, 0.0, 5.0);  //map can't be used as it works only for integers 

  float ADCreading = analogRead(voltageSensorPin); 
  float VIN = (ADCreading/1023.0)*5.0; 
    
    return VIN*((R1+R2)/R2); 
}


 //5.0*((R1+R2)/R2)


void setup() {
  Serial.begin(9600); 

}

void loop() {
  Serial.print("Analog Reading: "); 
  Serial.println(analogRead(voltageSensorPin)); 
  Serial.print("Voltage: "); 
  Serial.println(voltageReading()); 
  delay(500);
}
