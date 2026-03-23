#include <ESP32Servo.h>
#define M1LPWM_LEDC_CHANNEL 6  // LEDC channel to use
#define M1RPWM_LEDC_CHANNEL 7

#define motor1Lpwm 19
#define motor1Rpwm 18

#define M2LPWM_LEDC_CHANNEL 8  // LEDC channel to use
#define M2RPWM_LEDC_CHANNEL 9


// #define motor2Lpwm 13  //5
// #define motor2Rpwm 14  //17

#define M3LPWM_LEDC_CHANNEL 10  // LEDC channel to use
#define M3RPWM_LEDC_CHANNEL 11

#define motor3Lpwm 5   //13
#define motor3Rpwm 17  //14

#define M4LPWM_LEDC_CHANNEL 12  // LEDC channel to use
#define M4RPWM_LEDC_CHANNEL 13

#define motor4Lpwm 26   //13
#define motor4Rpwm 27  //14

#define buttonPin 25
#define coffeeDispenseButtonPin 14
#define statusLedPin 2 //Shows whether the operation is running or not

#define relay1In  22 // Water heater 
#define relay2In  21 // Coffee heater 

#define vulveRelayIn 23 

unsigned long waterTimer = millis(); 
unsigned long coffeeTimer = millis(); 
unsigned long waterVulveTimer = millis(); 
unsigned long coffeePowderMotorTimer = millis(); 
unsigned long milkPowderMotorTimer = millis(); 
unsigned long coffeePumpTimer = millis(); 
#define coffeeHeatTime 30 // second 
#define waterHeatTime  30 // second 
#define waterVulveTime 60 // second
#define coffeePumpTime 20 
#define milkPowderMotorTime 20 
#define coffeePowderMotorTime 20 
unsigned short coffeeHeaterFlag = 0; 
unsigned short waterHeaterFlag = 0; 
unsigned short waterVulveFlag = 0; // 0 = not started, 1 = vulve is open, 2 = vulve has been closed after opening for a while 
unsigned short coffeePowderMotorFlag = 0; // 0 = not started, 1 = motor is running, 2 = motor has been stopped  after running for a while 
unsigned short milkPowderMotorFlag = 0; // 0 = not started, 1 = motor is running, 2 = motor has been stopped  after running for a while
unsigned short coffeePumpFlag = 0; // 0 = not started, 1 = motor is running, 2 = motor has been stopped  after running for a while  



#define motorSpeed 150
int startFlag = 0 ; // Whether we have started the motor running sequence with button press.


void setup() {
  Serial.begin(115200); 
  ESP32PWM::allocateTimer(0);
  ledcSetup(M1LPWM_LEDC_CHANNEL, 1000, 8);  // Set LEDC channel, frequency, and resolution
  ledcSetup(M1RPWM_LEDC_CHANNEL, 1000, 8);

  ledcAttachPin(motor1Lpwm, M1LPWM_LEDC_CHANNEL);  // Attach the GPIO pin to the LEDC channel
  ledcAttachPin(motor1Rpwm, M1RPWM_LEDC_CHANNEL);

  // ledcSetup(M2RPWM_LEDC_CHANNEL, 1000, 8);
  // ledcSetup(M2RPWM_LEDC_CHANNEL, 1000, 8);

  // ledcAttachPin(motor2Lpwm, M2LPWM_LEDC_CHANNEL);  // Attach the GPIO pin to the LEDC channel
  // ledcAttachPin(motor2Rpwm, M2RPWM_LEDC_CHANNEL);


  ledcSetup(M3RPWM_LEDC_CHANNEL, 1000, 8);
  ledcSetup(M3LPWM_LEDC_CHANNEL, 1000, 8);

  ledcAttachPin(motor3Lpwm, M3LPWM_LEDC_CHANNEL);  // Attach the GPIO pin to the LEDC channel
  ledcAttachPin(motor3Rpwm, M3RPWM_LEDC_CHANNEL);

  ledcSetup(M4RPWM_LEDC_CHANNEL, 1000, 8);
  ledcSetup(M4LPWM_LEDC_CHANNEL, 1000, 8);

  ledcAttachPin(motor4Lpwm, M4LPWM_LEDC_CHANNEL);  // Attach the GPIO pin to the LEDC channel
  ledcAttachPin(motor4Rpwm, M4RPWM_LEDC_CHANNEL);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(coffeeDispenseButtonPin, INPUT_PULLUP); 

  pinMode(relay1In,  OUTPUT); 
  pinMode(relay2In, OUTPUT); 
  pinMode(statusLedPin, OUTPUT); 
  pinMode(vulveRelayIn, OUTPUT); 
  digitalWrite(relay1In, HIGH); 
  digitalWrite(relay2In, HIGH); 
  digitalWrite(vulveRelayIn, HIGH); 



  // put your setup code here, to run once:
}



void loop() { 

  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(statusLedPin,  HIGH); 
    delay(500);  //Debounce delay
    Serial.println("Pressed!"); 
    startFlag = 1 - startFlag;
    if (startFlag == 0) {
      resetProcess(); 
      digitalWrite(statusLedPin, LOW); 
    }
  }

 if (startFlag == 1) {
  digitalWrite(relay1In, LOW); 
  delay(60*1000); 
  digitalWrite(relay1In, HIGH); 

  runMotor1(motorSpeed); 
  runMotor2(motorSpeed); 
  delay(5*1000); 
  stopMotor1(); 
  delay(5*1000); 
  stopMotor2(); 

  
  digitalWrite(vulveRelayIn, LOW); 
  delay(240*1000); 
  digitalWrite(vulveRelayIn, HIGH); 

  digitalWrite(relay2In, LOW); 
  delay(1*60*1000); 
  digitalWrite(relay2In, HIGH); 

  for(int i = 0; i < 10; i++)
  {
    digitalWrite(statusLedPin, LOW); 
    delay(1000); 
    digitalWrite(statusLedPin, HIGH); 
    delay(1000); 
  }
  delay(2000); 



  for(int i = 0; i < 10; i++)
  {
    digitalWrite(statusLedPin, LOW); 
    delay(1000); 
    digitalWrite(statusLedPin, HIGH); 
    delay(1000); 
  }
  delay(2000); 


    for(int i = 0; i < 20; i++)
  {
    digitalWrite(statusLedPin, LOW); 
    delay(500); 
    digitalWrite(statusLedPin, HIGH); 
    delay(500); 
  }
  delay(2000); 

  coffeePumpFlag = 1; 


  startFlag = 0; 
  digitalWrite(statusLedPin, LOW); 

 }

 if( digitalRead(coffeeDispenseButtonPin)==LOW)
 {
    runMotor3(150); 
    delay(1500); 
    stopMotor3(); 
 }
}


void resetProcess()
{
      digitalWrite(relay2In, HIGH); 
      coffeeHeaterFlag = 0; 
      digitalWrite(relay1In, HIGH); 
      waterHeaterFlag = 0; 
      digitalWrite(vulveRelayIn, HIGH);  
      waterVulveFlag = 0; 
      stopMotor1();
      coffeePowderMotorFlag = 0; 
      stopMotor2();
      milkPowderMotorFlag = 0; 
      stopMotor3(); // Coffee pump motor 
      coffeePumpFlag = 0; 
}


void runMotor1(int Speed) {
  ledcWrite(M1LPWM_LEDC_CHANNEL, 0);
  ledcWrite(M1RPWM_LEDC_CHANNEL, Speed);
}

void stopMotor1() {
  ledcWrite(M1LPWM_LEDC_CHANNEL, 0);
  ledcWrite(M1RPWM_LEDC_CHANNEL, 0);
}



void runMotor2(int Speed) {
  ledcWrite(M3LPWM_LEDC_CHANNEL, 0);
  ledcWrite(M3RPWM_LEDC_CHANNEL, Speed);
}

void stopMotor2() {
  ledcWrite(M3LPWM_LEDC_CHANNEL, 0);
  ledcWrite(M3RPWM_LEDC_CHANNEL, 0);
}


void runMotor3(int Speed) {
  ledcWrite(M4RPWM_LEDC_CHANNEL, Speed);

  ledcWrite(M4LPWM_LEDC_CHANNEL, 0);
}

void stopMotor3() {
  ledcWrite(M4LPWM_LEDC_CHANNEL, 0);
  ledcWrite(M4RPWM_LEDC_CHANNEL, 0);
}



  //   if(waterHeaterFlag==0)   //Start heating the water 
  //   {
  //     waterHeaterFlag = 1; 
  //     waterTimer = millis(); 
  //     digitalWrite(relay1In, LOW); 
  //     // Open the vulve for pouring water into the cup. 
  //   }
  //   if(waterHeaterFlag==1 && millis() - waterTimer > waterHeatTime*1000)
  //   {
  //     digitalWrite(relay1In, HIGH);  
  //     waterHeaterFlag = 2; // Water heating is done 
  //     //Pouring coffee powder. 
  //     runMotor1(motorSpeed); 
  //     coffeePowderMotorFlag = 1; 
  //     coffeePowderMotorTimer = millis(); 
  //   }

  //   if(coffeePowderMotorFlag==1 && millis() - coffeePowderMotorTimer > coffeePowderMotorTime * 1000)
  //   {
  //     stopMotor1(); 
  //     coffeePowderMotorFlag = 2; // coffee Powder pouring is done 
  //     //Pouring milk powder
  //     runMotor2(motorSpeed); 
  //     milkPowderMotorFlag = 1; 
  //     milkPowderMotorTimer = millis(); 
  //   }

  //   if(milkPowderMotorFlag==1 && millis() - milkPowderMotorTimer > milkPowderMotorTime * 1000)
  //   {
  //     stopMotor2(); 
  //     milkPowderMotorFlag = 2; //milk Powder pouring is done 
  //     //Pouring water 
  //     waterVulveFlag = 1; 
  //     digitalWrite(vulveRelayIn, LOW); //Opening the vulve to pour water into the cup. 
  //   }

  //   if(waterVulveFlag == 1 && millis() - waterVulveTimer > waterVulveTime*1000)
  //   {
  //     digitalWrite(vulveRelayIn, HIGH); //Closing the relay. 
  //     waterVulveFlag = 2; // Water pouring has been done. 
  //     //Starting the coffee heating process. 
  //     coffeeHeaterFlag = 1; 
  //     coffeeTimer = millis(); 
  //     digitalWrite(relay2In, LOW);
  //   }

  //   if(coffeeHeaterFlag==1 && millis() - coffeeTimer > coffeeHeatTime*1000)  
  //   {
  //     digitalWrite(relay2In, HIGH); 
  //     coffeeHeaterFlag = 2; // Coffee heating is done 
  //     runMotor3(motorSpeed); //Start pumping the coffee 
  //     coffeePumpFlag = 1; 
  //   }

  //   if(coffeePumpFlag ==1 && millis() - coffeePumpTimer > coffeePumpTime*1000)
  //   {
  //     coffeePumpFlag = 2; 
  //   }
  //   // digitalWrite(vulveRelayIn, LOW); 
  //   // delay(1000); 
  //   // digitalWrite(vulveRelayIn, HIGH); 
 

  //   // runMotor1(motorSpeed);
  //   // delay(5000);
  //   // stopMotor1();
  //   // delay(10);

  //   // runMotor3(motorSpeed);
  //   // delay(5000);
  //   // stopMotor3();
  //   // delay(10);

  //   // runMotor4(motorSpeed);
  //   // delay(5000);
  //   // stopMotor4();
  //   // delay(10);

  //   if(coffeePumpFlag == 2)
  //   {
  //     startFlag = 0; 
  //     resetProcess(); 
  // }