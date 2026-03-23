//This particular piece of project didn't work. Probable reason: The used ICs might be damaged or faulty. 

#include<Wire.h>

#define EEPROM_I2C_ADDRESS 0x50

//Byte to hold data read from EEPROM 
int readVal = 0;  

//Integer to hold number of address to fill and read from
int maxaddress = 100; 


// Function to write to EEPROM
void writeEEPROM(int address, byte val, int i2c_address)
{
  //Begin Transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address); 

   //Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));  //Most significant byte
  Wire.write((int)(address & 0xFF)); //Least Significant byte
 

  //Send data to be stored
  Wire.write(val); 

  //End the transmission
  Wire.endTransmission(); 

  //Add 5ms delay for EEPROM
  delay(5); 
  
}


//Function to read from EEPROM
byte readEEPROM(int address, int i2c_address)
{
  //Define byte ofre recieved data
  byte rcvData = 0xFF; 

  //Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address); 

  //Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));  //Most significant byte
  Wire.write((int)(address & 0xFF)); //Least Significant byte

  //End the transmission
  Wire.endTransmission(); 

  //Request one byte of data at current memory address
  Wire.requestFrom(i2c_address, 1); 

  //read the data and assign to variable
  rcvData = Wire.read(); 

  //Return the data as function output
  return rcvData; 

  
}

void setup()
{
  // Connect to I2C bus as master (without parameter)
  Wire.begin(); 

  //Setup Serial Monitor
  Serial.begin(9600); 

  //Writing values to EEPROM
  for(int address = 0; address <=maxaddress; address++)
  {
    writeEEPROM(30, address, EEPROM_I2C_ADDRESS); 
  }

  for(int address = 0; address <=maxaddress; address++)
  {
    //read value from EEPROM
    readVal = readEEPROM(address, EEPROM_I2C_ADDRESS); 
    Serial.print("Address = "); 
    Serial.print(address); 
    Serial.print(" Value = "); 
    Serial.print(readVal); 
    Serial.print('\n'); 
  }
  
delay(500); 
  

}


void loop()
{

}
