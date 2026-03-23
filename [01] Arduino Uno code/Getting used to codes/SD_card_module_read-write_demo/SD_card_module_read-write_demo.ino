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
  servoPosFile = SD.open("servo_Positions.txt", FILE_WRITE); 
}

byte angle = 0; 

byte state = 0; 


void loop()
{
  angle = map(analogRead(potPin), 0, 1023, 3, 177); 
  servoA.write(angle);
  
  if(state==1)
  {
   // Serial.println("Inside writing function"); 
 
    servoPosFile.println(angle); 
    Serial.println(angle); 
  }

  if(Serial.available() )
  {
    char mes = Serial.read(); 
    Serial.println(mes); 
    if(mes=='1')
    {
      state = 1; 
      servoPosFile = SD.open("servo_Positions.txt"); 
    }
    else if(mes=='2')
    {
      state = 0; 
      servoPosFile.close(); 
    }
    
  }
  
  delay(10); 

}
