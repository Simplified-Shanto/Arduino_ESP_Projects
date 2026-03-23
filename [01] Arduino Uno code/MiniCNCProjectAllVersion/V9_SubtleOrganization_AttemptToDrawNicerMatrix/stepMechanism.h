boolean positionInitialized = false; 

short currentX = 0; //The current X position of the pen. 
#define maxXposition  50  //The maximum X position of the pen. 
#define minXposition  0    //Minimum X position of the pen.

short currentY = 0; //The current Y position of the pen. 
#define maxYposition  65  //Maximum Y position of the pen. 
#define minYposition  0    //Minimum Y position of the pen. 


#define in1 2 //A+ 
#define in2 3 //A-
#define in3 4 //B+
#define in4 5 //B-
#define verticalSwitch 9


//Pin declaration for horizontal set up
#define In1  10
#define In2  11
#define In3  A0
#define In4  12
#define horizontalSwitch A1
 

#define highTime 2   //The period of phase being turned on in millisecond. 

void stepBackward(int stepCount, int switchGap)  //function for one backward step
{
  if(positionInitialized == true)  //We'll not constrain the value while the position isn't initialized yet. 
  {
  stepCount = min(currentX, stepCount); //Limiting the backward movement 
  }
  
 for(int i = 1; i<=stepCount; i++)
 {
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 
  
  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------

  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 

   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap);

   currentX--; 
 }
}

void stepForward(int stepCount, int switchGap)  //Function for one forward step
{
  stepCount = min(maxXposition - currentX, stepCount); //Limiting the forward movement within the range. 
  
 for(int i = 1; i<=stepCount; i++)
 {
  //Turning on phase B in +-
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 
  //--------------------------------------
  
  //Turning on phase A in +-
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
 delay(switchGap); 


   //Turning on phase B in -+
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay(switchGap); 

  
  //Turning phase A in -+
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  delay(switchGap); 

  currentX++; 
 }
}


void stepLeft(int stepCount, int switchGap)  //function for one backward step
{
  stepCount = min(stepCount, maxYposition - currentY);   //Limiting the Y movement within the range 
                                                         //minYposition and maxYposition
  
 for(int i = 1; i<=stepCount; i++)
 {
  //Turning on phase A in +-
  digitalWrite(In1, HIGH); 
  digitalWrite(In2, LOW); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 

  //Turning on phase B in +-
  digitalWrite(In3, HIGH); 
  digitalWrite(In4, LOW); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
  //--------------------------------------

  //Turning phase A in -+
  digitalWrite(In1, LOW); 
  digitalWrite(In2, HIGH); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 
  delay(switchGap); 

   //Turning on phase B in -+
  digitalWrite(In3, LOW); 
  digitalWrite(In4, HIGH); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 

   currentY++; //Updating the Y position at the same time of changing position. 
 }


}


void stepRight(int stepCount, int switchGap)  //Function for one forward step
{
  if(positionInitialized == true)   //Avoiding the range constrainer when the position is not initialized yet. 
  {
    stepCount = min(stepCount, currentY); //Once initilized, each requested number of steps is bound to be within the range of
                                          //movement. 
  }
  
 for(int i = 1; i<=stepCount; i++)
 {
  //Turning on phase B in +-
  digitalWrite(In3, HIGH); 
  digitalWrite(In4, LOW); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 
  //--------------------------------------
  
  //Turning on phase A in +-
  digitalWrite(In1, HIGH); 
  digitalWrite(In2, LOW); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 



   //Turning on phase B in -+
  digitalWrite(In3, LOW); 
  digitalWrite(In4, HIGH); 
  delay(highTime); 
  //Turning off phase B
  digitalWrite(In3, LOW); 
  digitalWrite(In4, LOW); 
  delay(switchGap); 

  
  //Turning phase A in -+
  digitalWrite(In1, LOW); 
  digitalWrite(In2, HIGH); 
  delay(highTime); 
  //Turning off phase A
  digitalWrite(In1, LOW); 
  digitalWrite(In2, LOW); 
  delay(switchGap); 

  currentY--; 
 }
}
