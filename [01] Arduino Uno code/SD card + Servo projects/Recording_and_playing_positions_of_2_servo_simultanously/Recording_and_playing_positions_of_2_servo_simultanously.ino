 #include<SPI.h> 
#include<Servo.h> 
#include<SD.h> 

Servo servoX;  //The X axis servo 
Servo servoY;  //The y axis servo

 
#define chipSelect 4
#define joyX       analogRead(A0)  //X axis value of the Joystick
#define joyY       analogRead(A1)  //Y axis value of the Joystick
#define joyButton  digitalRead(A2)  //Joystick button
#define buttonPin  3   //The recording button
#define servoXpin  9   //Digital pin 9
#define servoYpin  5   //Digital pin 5

File positionFile; 

void setup() {
  Serial.begin(9600); 
  servoX.attach(servoXpin); 
  servoY.attach(servoYpin); 
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(joyButton, INPUT_PULLUP); 

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

 unsigned short xAngle = 0;
 unsigned short yAngle = 0;  
byte state = 0; 
byte trigger = 0;

void loop() {
  if(joyX > 600 && xAngle < 180)
  {
    xAngle+=2; 
  }
  if(joyX < 400 && xAngle > 0)
  {
    xAngle-=2; 
  }
  if(joyY > 600 && yAngle < 180)
  {
    yAngle+=2; 
  }
  if(joyY < 400 && yAngle > 0)
  {
    yAngle-=2; 
  }

  

  if(digitalRead(buttonPin)==0)
  {
    //Triggers the variable to 1; indicates that next time 
    //the button is released, we should start playing back 
    //the positions. 
    //unsigned long long StartLog = millis(); 

     trigger = 1; 
     
    positionFile = SD.open("pos.txt", FILE_WRITE); 

    if(positionFile)
    {  
      positionFile.print(xAngle); 
      positionFile.print(','); 
      positionFile.println(yAngle); 
      positionFile.close(); 

      servoX.write(xAngle); 
      servoY.write(yAngle); 
    }
    else
    {
      Serial.println("Couldn't open file :( for writing!"); 
    }

    /*
    Serial.print("Saving time: "); 
     StartLog = millis() - StartLog; 
    Serial.print(float(StartLog)); 
    Serial.println(" ms"); 
    
    servoA.write(angle); 
    */
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
              //long long StartLog = millis(); //Retrieving operation start. 
              
              Serial.println("Starting playback!  :)"); 
              String XYvalue = positionFile.readStringUntil('\n');   //Reads and store a complete line to XYvalue
              Serial.println(XYvalue);  
              String Y = XYvalue.substring(XYvalue.indexOf(',')+1);    //Stores the X value before comma
              String X = XYvalue.substring(0, XYvalue.indexOf(','));   //Stores the Y value from index 0 to indexOf(,) - 1

              servoX.write(X.toInt()); 
              servoY.write(Y.toInt()); 
              
              
              delay(30);   /*It takes about 15 ms to open the file and write angle value to it. + there's a 15 ms delay at each run of void loop() 
                             So the delay at this position is made 30 ms to get the recording and playing time almost equal. 

                            */


                 /*
              Serial.print("Retrieving time: "); 
              StartLog = millis() - StartLog; 
              Serial.print(float(StartLog)); 
              Serial.println(" ms"); 
                */
              
            }
    
          positionFile.close();  //Closing the file
          SD.remove("pos.txt");   //Deleting the file permanently thus the positions of new recording are not appended to previous positons. 
                                  //There might be other efficient way to clear the content of the file- but I don't know that yet. 
        
      
                                      
    
    }
    else
    {
      Serial.println("Couldn't open the file :("); 
    }
    trigger = 0; 
  }
  else
  {
      servoX.write(xAngle); 
      servoY.write(yAngle); 
   
  }

  delay(15); 
}
