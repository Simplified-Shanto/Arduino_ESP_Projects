#include "Wire.h" 

#define EEPROM_I2C_ADDRESS 0x0

#define maxaddress 230

int readVal = 0; 

void writeEEPROM(int address, byte val, int i2c_address)
{
  // Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address);
 
  // Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
 
  // Send data to be stored
  Wire.write(val);
 
  // End the transmission
  Wire.endTransmission();
 
  // Add 5ms delay for EEPROM
  delay(5);
}

// Function to read from EEPROM
byte readEEPROM(int address, int i2c_address)
{
  // Define byte for received data
  byte rcvData = 0xFF;
 
  // Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address);
 
  // Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
 
  // End the transmission
  Wire.endTransmission();
 
  // Request one byte of data at current memory address
  Wire.requestFrom(i2c_address, 1);
 
  // Read the data and assign to variable
  rcvData =  Wire.read();
 
  // Return the data as function output
  return rcvData;
}



void setup() {
  Serial.begin(9600); 
  Wire.begin(); 

  Serial.println("Starting writing data: "); 
  for(int address = 0; address <= maxaddress; address++)
  {
  writeEEPROM(address, address, EEPROM_I2C_ADDRESS);
  Serial.println("Writing at "); 
  Serial.println(address); 
  delay(10); 
  }


  Serial.println("Starting reading data:"); 

  for(int address = 0; address <= maxaddress; address++)
  {
    readVal  = readEEPROM(address, EEPROM_I2C_ADDRESS); 
    Serial.print("ADDR = "); 
    Serial.print(address); 
    Serial.print("\t"); 
    Serial.println(readVal); 
    delay(10); 
  }
  Serial.println("Retrieving data has been finished"); 
  
}

void loop() {
  
}
