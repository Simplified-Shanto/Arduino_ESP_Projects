
//Pin declaration for the 74HC595 shift register
#define latchPin 8  //Pin 12 of 74HC595 shift register
#define clockPin 4  //Pin 11 of the 74HC595 shift register
#define dataPin  2 //Pin 14 of the 74HC595 shift register

boolean extraPinState[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Initially all extra pins are turned low

/*We can use the following pins of the 74HC595 shift register as new digital output pins: 
 * Shift register pins                  New digital pin
 * ^^^^^^^^^^^^^^^^^^^                  ^^^^^^^^^^^^^^^
 *        15                                  14  
 *        1                                   15
 *        2                                   16
 *        3                                   17
 *        4                                   18
 *        5                                   19
 *        6                                   20
 *        7                                   21
 */        

#define leftMotorEnablePin 5
#define rightMotorEnablePin 6
//Pin declaration for left motor. 
#define in1   7
#define in2  9

//Pin declaration for right motor. 
#define in3  10
#define in4  11



//Pin declaration for the unused 1 motor of the second l293d motor driver. 
#define unusedMotorIn3 15
#define unusedMotorIn4 21


void setup() {
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, OUTPUT); 

  //Pulling all extra pins to LOW initially
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 0); 
  digitalWrite(latchPin, HIGH); 

  //Declaring 4 wheel's motor's common enable pin and setting it to 0 (In range 0 to 255)
   pinMode(leftMotorEnablePin, OUTPUT);
   analogWrite(leftMotorEnablePin, 0); 
   pinMode(rightMotorEnablePin, OUTPUT); 
   analogWrite(rightMotorEnablePin, 0); 
   pinMode(in1, OUTPUT); 
   pinMode(in2, OUTPUT); 
   pinMode(in3, OUTPUT); 
   pinMode(in4, OUTPUT); 
    
   
  
  
  delay(100); 

  Serial.begin(9600); 
}


unsigned long preMillis = millis(); 

int actionValue = 150; 
int timeThreshold = 100; //After how much time we will call Stop(); 


String command = "a";   //Command received via Serial
char Action = 'a'; //Which action we will take. Example: Mode setup
String speedString = "x"; 
unsigned short carMode = 1; // 1 - Joystick driving mood
                            // 2- Obstacle avoidance mood

/*
 * Control Characters
 * Forward - 'f'
 * Backward - 'b'
 * Left - 'l'
 * Right - 'r'
 * 
 * 5 servos on the robotic arm (considering 2 cont. rot. servos on the second  
 * joint as a single one) starting from the first one at the base:  'u', 'v' 'w', 'x', 'y'
 *
 * Servo positions are changed commands "character:1." for increment" and "character:-1." for decrement
 * Here character = u, v, w, x, y  //v controls 2 servo motors
 * Gripper is controlled with character 'z'
 * 
 * Mode setup - 'm' 
 * OA variables settings - '0' to last index of oaSettings array. 
 * 
 * Serial command print format - "Command:Value" for example: "f:120." means go forward with a pwm of 120
 *                                                            "u:120." means to set the base servo to 120 degree. 
 *                                                            "m:1." means to set the car to mode 1 or driving mode. 
 *                                                            "1:120." means set oaSettings[1] to 120
 */
 
     int pwm = 250;                              
void loop() {
    goForward(pwm);  
    delay(1000); 
     Stop();

    goLeft(pwm); 
    delay(1000);
    Stop(); 

    goForward(pwm); 
    delay(1000); 
    Stop(); 

    goLeft(pwm); 
    delay(1000); 
    Stop(); 
    
    goBackward(pwm); 
    delay(1000); 
     Stop(); 




  /*
 
   if (Serial.available()) {
    command = Serial.readStringUntil('.');  
    Action = command[0]; //The type of action the remote wants us to take. 
    speedString = command.substring(2, command.length()); 
    actionValue = speedString.toInt(); 
      
    preMillis = millis(); 

        switch(Action) //Which action we are going to take. 
        {
        case 'f': 
        if(carMode==1){        
       goForward(actionValue); 
        timeThreshold = 100; 
        }
        break; 
        
        case 'b': 
        if(carMode==1){
        goBackward(actionValue); 
        timeThreshold = 100; 
        }
        break; 
        case 'l': //Left direction
        if(carMode==1){
        goLeft(actionValue);  //Turning half at a speed of going. 
        timeThreshold = 60; 
        }
        break; 
        
        case 'r': //Right direction
        if(carMode==1){
        goRight(actionValue); 
        timeThreshold = 60;   //Turning at the half speed of going
        }
        break; 

        case 'm': //Mode setup 
        {
          Stop(); 
          sensorServo.write(90); //Making the sensor front facing in the beginning of all modes
          delay(1000); 
          carMode = actionValue; 
        }
        break; 

        case 'u': //The base continuous rotation servo of the arm
        {
         if(actionValue==1){     armServo1.write(CRSspeed+90);       }  //moving in the forward direction. 
         else { armServo1.write(90-CRSspeed); }  //moving in the backward direction
         delay(CRSruntime);   //for a short time. 
         armServo1.write(90); //then stopping the motor from rotating. 
        }
        break; 

        case 'v': //The left and right CSR from the base of the arm. 
        {
          servoPositions[1]+=actionValue; //Incrementing/Decrementing. 
          servoPositions[1] = max(servoPositions[1], 2); //Taking care of lower bound of angle
          servoPositions[1] = min(servoPositions[1], 178); //Taking care of upper bound of angle
          servoPositions[2]-=actionValue; //Doing the opposite for the opposite side servo motor. 
          servoPositions[2] = max(servoPositions[2], 2); //Taking care of lower bound of angle
          servoPositions[2] = min(servoPositions[2], 178); //Taking care of upper bound of angle

          if(180 - servoPositions[1]!=servoPositions[2])
          {
            sensorServo.write(130); 
            delay(500); 
            sensorServo.write(90); 
            delay(500); 
          }
          else
          {
          armServo2Left.write(servoPositions[1]); 
          armServo2Right.write(servoPositions[2]); 
          }
        }
        break; 

        case 'w': //Third CR servo counting from the base of the arm. 
        {
         if(actionValue==1){     armServo3.write(CRSspeed+90);       }  //moving in the forward direction. 
         else { armServo3.write(90-CRSspeed); }  //moving in the backward direction
         delay(CRSruntime);   //for a short time. 
         armServo3.write(90); //then stopping the motor from rotating. 
        }
        break; 

        case 'x': //Fourth servo counting from the base of the arm. 
        {
           if(actionValue==1){     armServo4.write(CRSspeed+90);       }  //moving in the forward direction. 
         else { armServo4.write(90-CRSspeed); }  //moving in the backward direction
         delay(CRSruntime);   //for a short time. 
         armServo4.write(90); //then stopping the motor from rotating. 
        }
        break; 

        case 'y': //Fifth servo motor. 
        {
           servoPositions[5]+=2*actionValue; //Incrementing/Decrementing. 
          servoPositions[5] = max(servoPositions[5], 2); //Taking care of lower bound of angle
          servoPositions[5] = min(servoPositions[5], 178); //Taking care of upper bound of angle
          armServo5.write(servoPositions[5]); 
        }
        break;

         case 'z': //The gripper mechanism is implemented using gear motor. 
        {
            if(actionValue == 1)
          {
            DigitalWrite(gripperIn1, HIGH); 
            DigitalWrite(gripperIn2, LOW); 
            delay(10); 
            DigitalWrite(gripperIn1, LOW); 
          }
          else if(actionValue == -1)
          {
            DigitalWrite(gripperIn1, LOW); 
            DigitalWrite(gripperIn2, HIGH); 
            delay(10); 
            DigitalWrite(gripperIn2, LOW); 
          }
        }
        break;
        
         default: //"c:val." here c comes as 1,2,3,.... indicating the index of the changed OA settings. 
      {
        oaSettingsValue[Action - '0'] = actionValue; 
      }     
   } 
   }
   else 
   {
    if(carMode==1 && millis() - preMillis > timeThreshold) //We will stop only when in mode-1 joystick driving mode. 
    {
      Stop(); 
      preMillis = millis(); 
    }
   }

    
    if(carMode==2) //Whether car is in collission avoidance mode. 
    {
      middleDistance = calculateDistance(); 
// serialPrint('M', middleDistance); 

      if(middleDistance < oaSettingsValue[4]) //oaSettingsValue[4] = safeDistance
      {
       Stop(); 
       sensorServo.write(0);                //Moving US sensor to the right
       delay(1000);                          //Keeping the sensor steady for 1000 ms. 
       rightDistance = calculateDistance();  //returns distance in inch unit
     //  serialPrint('R', rightDistance);      //Sending the reading to the controller.
       delay(500); 
       
       sensorServo.write(180); //Moving ultrasonic sensor to the left
       delay(1000);       //Keeping the sensor steady on the servo to get a stable reading. 
       leftDistance = calculateDistance();  //Calculating left distance. 
      // serialPrint('L', leftDistance);      //Sending the data to the controller. 
       delay(500); 
       
 
       sensorServo.write(90);               //Taking back the sensor on the servo to front direction 
       delay(1500);                          //Having a short delay before going to newly found direction. 
      
    
        if(rightDistance >= oaSettingsValue[4] && rightDistance >= leftDistance)  //Whether right side has enough safe
       {
        goRight(oaSettingsValue[2]);  
        delay(oaSettingsValue[3]); 
       }
       else if(leftDistance >= oaSettingsValue[4])   //oaSettingsValue[4]  = safe distance. 
       {
          goLeft(oaSettingsValue[2]); 
          delay(oaSettingsValue[3]);
       }
      else{
        goBackward(oaSettingsValue[0]); 
        delay(oaSettingsValue[1]); 
       }
       
      } 
      else 
      {
        goForward(oaSettingsValue[0]); 
      }
    }
*/
    

    
    
}



//digtalWrite() function for the new extra pins
void DigitalWrite(int extraPinNumber, int state)
{
  extraPinState[extraPinNumber - 14] = state; 
  /*Since there's already 13 pins in arduino UNO and we are counting the extra pins from 14....to 21 */
  unsigned short decimalValue  = 0; 
  for(int i = 0; i <= 7; i++)  //Converting the 8 bit bit pattern to decimalvalue
  { 
    decimalValue+= (ceil(pow(2, i))*extraPinState[i]); 
  }
  digitalWrite(latchPin, LOW); //Don't changing the pin state while sending data serially
  shiftOut(dataPin, clockPin, MSBFIRST, decimalValue); 

  digitalWrite(latchPin, HIGH); 
}



// int calculateDistance(){ 
  
//   digitalWrite(trigPin, LOW); //Extra pin number 14
//   delayMicroseconds(2);
//   // Sets the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trigPin, HIGH); 
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//  long duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
//   return duration*0.0068; //returns distance in inch. 
// }


void Stop()
{
  analogWrite(leftMotorEnablePin, 0); 
  analogWrite(rightMotorEnablePin, 0); 
}

void rightForward(int actionValue) //Sets the right motor to move forward
{
  analogWrite(rightMotorEnablePin, actionValue); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
}

void rightBackward(int actionValue)
{
   analogWrite(rightMotorEnablePin, actionValue);  
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
}

void leftForward(int actionValue)
{
 analogWrite(leftMotorEnablePin, actionValue); 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  
}

void leftBackward(int actionValue)
{
   analogWrite(leftMotorEnablePin, actionValue);  
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
}


void goForward(int actionValue)
{
 rightForward(actionValue); 
 leftForward(actionValue); 
}

void goBackward(int actionValue)
{
  rightBackward(actionValue); 
  leftBackward(actionValue); 
}

void goLeft(int actionValue)
{
 rightForward(actionValue); 
 leftBackward(actionValue); 
}


void goRight(int actionValue)
{
    leftForward(actionValue); 
    rightBackward(actionValue); 
}
