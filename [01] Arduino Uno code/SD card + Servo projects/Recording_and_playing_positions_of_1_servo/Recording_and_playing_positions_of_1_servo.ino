/*Work flow; 
 * There'll be one button. 
 * If the knob is rotated is pressed without pressing the button then, 
 * the servo will just change it's position, the positions will not 
 * be recorded. 
 * 
 * If the knob is rotated the button being pressed, then the positions
 * will be recorded and played back after 1 second the button has
 * been released. 
 * 
 * Target achieved. 
 */
 
/* This challenge features 2 servo motors connected in X and Y axis. 
 * 
 */

#include<SPI.h> 
#include<Servo.h> 
#include<SD.h> 

Servo servoA; 
#define chipSelect 4
#define potPin     A0
#define servoPin   9
#define buttonPin  3
#define ledPin 

File positionFile; 

void setup() {
  Serial.begin(9600); 
  servoA.attach(servoPin); 
  pinMode(buttonPin, INPUT_PULLUP); 

  Serial.println("Initializing SD card..."); 
 if(!SD.begin(chipSelect))
 {
  Serial.println("SD card failed or not inserted:("); 
  //Do nothing after this. 
  while(1)
  {
    ; 
  }
 }

 Serial.println("Card initialized."); 
  positionFile = SD.open("pos.txt", FILE_WRITE); 
}


int angle = 0; 
byte state = 0; 
byte trigger = 0;

void loop() {
  angle = map(analogRead(potPin), 0, 1023, 0, 180); 
  

  if(digitalRead(buttonPin)==0)
  {
    //Triggers the variable to 1; indicates that next time 
    //the button is released, we should start playing back 
    //the positions. 
    trigger = 1; 

    unsigned long long StartLog = millis(); 
    
    positionFile = SD.open("pos.txt", FILE_WRITE); 

    if(positionFile)
    {  
    positionFile.println(angle); 
    positionFile.close(); 
    Serial.println(angle); 
    }
    else
    {
      Serial.println("Couldn't open file :( for writing!"); 
    }

    Serial.print("Saving time: "); 
     StartLog = millis() - StartLog; 
    Serial.print(float(StartLog)); 
    Serial.println(" ms"); 
    
    servoA.write(angle); 
  }
  else if(trigger == 1)
  {
        delay(1000); 
        positionFile = SD.open("pos.txt", FILE_READ); 
    
        
        if(positionFile)
        {
          Serial.println("File opened successfully for reading:)"); 
            while(positionFile.available())
            {
              long long StartLog = millis(); //Retrieving operation start. 

              
              String angleValue = positionFile.readStringUntil('\n');
              Serial.println(angleValue);  
              servoA.write(angleValue.toInt()); 
              delay(30);   /*It takes about 15 ms to open the file and write angle value to it. + there's a 15 ms delay at each run of void loop() 
                             So the delay at this position is made 30 ms to get the recording and playing time almost equal. 

                            */

              Serial.print("Retrieving time: "); 
              StartLog = millis() - StartLog; 
    Serial.print(float(StartLog)); 
    Serial.println(" ms"); 
            }
    
          positionFile.close(); 
          SD.remove("pos.txt"); 
    
    }
    else
    {
      Serial.println("Couldn't open the file :("); 
    }
    trigger = 0; 
  }
  else
  {
    servoA.write(angle); 
   // Serial.println(angle); 
  }

  delay(15); 
}
