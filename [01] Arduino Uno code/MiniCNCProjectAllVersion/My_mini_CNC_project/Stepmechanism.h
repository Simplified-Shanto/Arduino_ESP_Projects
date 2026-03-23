#define in1 2 //A+ 
#define in2 3 //A-
#define in3 4 //B+
#define in4 5 //B-

//Pin definition for the horizontal stepper. 
#define In1 A7
#define In2 A6
#define In3 11
#define In4 10

#define verticalSwitchPin 7   //Switch which indicates the initial position of the vertical stepper motor. 
#define horizontalSwitchPin 6 //Switch which indicates the initial position of the stepper set up. 



void VstepBackward(int stepCount, int switchGap)  //function for one backward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 

  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------

  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 

   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
 }
}


void VstepForward(int stepCount, int switchGap)  //Function for one forward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------
  
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 



   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 

  
  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  
 }
}



void HstepBackward(int stepCount, int switchGap)  //function for one backward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase A in +-
  digitalWrite(In1, HIGH); 
  digitalWrite(In2, LOW); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 

  //Turning on phase B in +-
  digitalWrite(In3, HIGH); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
  //--------------------------------------

  //Turning phase A in -+
  digitalWrite(In1, LOW); 
  digitalWrite(In2, HIGH); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 
  delay(switchGap); 

   //Turning on phase B in -+
  digitalWrite(In3, LOW); 
  digitalWrite(In4, HIGH); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
 }
}


void HstepForward(int stepCount, int switchGap)  //Function for one forward step
{
 for(int i = 0; i<=stepCount; i++)
 {
  //Turning on phase B in +-
  digitalWrite(In3, HIGH); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
  //--------------------------------------
  
  //Turning on phase A in +-
  digitalWrite(In1, HIGH); 
  digitalWrite(In2, LOW); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 



   //Turning on phase B in -+
  digitalWrite(In3, LOW); 
  digitalWrite(In4, HIGH); 
  delay(switchGap); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 

  
  //Turning phase A in -+
  digitalWrite(In1, LOW); 
  digitalWrite(In2, HIGH); 
  delay(switchGap); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 
  delay(switchGap); 
  
 }
}




void initializePosition()
{
  boolean positionInitialized = false; 
  while(positionInitialized == false)
  {
    if(digitalRead(horizontalSwitchPin)!=0)
    {
      positionInitialized = true; 
    }
    else
    {
      HstepBackward(1, 10); 
    }
  }


    delay(500); 
    
  positionInitialized = false; 
    while(positionInitialized == false)
  {
    if(digitalRead(verticalSwitchPin)!=0)
    {
      positionInitialized = true; 
    }
    else
    {
      VstepBackward(1, 10); 
    }
  }
}
