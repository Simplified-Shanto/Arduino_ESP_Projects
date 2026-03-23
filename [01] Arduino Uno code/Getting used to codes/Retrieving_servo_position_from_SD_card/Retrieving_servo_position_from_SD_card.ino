#include <SPI.h> 
#include <SD.h> 
#include <Servo.h> 

File servoPosFile; 
Servo servoA; 
#define servoPin 9
#define potPin  A0

void setup()
{
  servoA.attach(servoPin); 
  //Open serial communications and wait for port to open: 
  Serial.begin(9600); 
  while(!Serial)
  {
    ; //wait for serial port to connect.  
  }

  Serial.print("Initializing SD card..."); 
  if(!SD.begin(4))
  {
    Serial.println("initialization failed!"); 
    while(1); 
  }
  Serial.println("initialization done"); 
  servoPosFile = SD.open("servo_Positions.txt", FILE_READ); 
}

byte angle = 0; 
String data; 

void loop()
{
  
  while(servoPosFile.available())
  {
    data = servoPosFile.read(); 
    angle = data.toInt(); 
    Serial.println(angle); 
    servoA.write(angle); 
    delay(15); 
  }

  servoPosFile.close(); 

  Serial.println("Retrieving completed"); 
  
}
