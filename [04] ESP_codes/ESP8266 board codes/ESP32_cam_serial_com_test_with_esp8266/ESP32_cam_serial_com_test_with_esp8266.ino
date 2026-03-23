/*
Inteneded board: ESP8266
This code was written on 3-11-2023 to test whether 
we were getting serial outputs from an ESP32 CAM module. 

 */


 #define ledPin 5

 

 void setup()
 {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);   //set the LED pin mode
  pinMode(LED_BUILTIN, OUTPUT); 
 }


String command; 

 void loop()
 {
   if (Serial.available()) {
    command = Serial.readStringUntil('.');  
    Serial.print("Got message!"); 
    char Action = command[0]; //The type of action the remote wants us to take. 
    
    switch(Action)
    {
     case 'f': 
           
          digitalWrite(LED_BUILTIN, HIGH); 

        break; 
        case 'b': 
        
          digitalWrite(LED_BUILTIN, LOW); 
       
      default: 
      break; 
   }

   }
   
 }
 
