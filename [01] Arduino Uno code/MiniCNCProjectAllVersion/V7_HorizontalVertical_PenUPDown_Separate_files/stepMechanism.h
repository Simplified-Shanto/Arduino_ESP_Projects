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
 for(int i = 0; i<=stepCount; i++)
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
 }
}

void stepForward(int stepCount, int switchGap)  //Function for one forward step
{
 for(int i = 0; i<=stepCount; i++)
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
  
 }
}


void stepLeft(int stepCount, int switchGap)  //function for one backward step
{
 for(int i = 0; i<=stepCount; i++)
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
 }
}


void stepRight(int stepCount, int switchGap)  //Function for one forward step
{
 for(int i = 0; i<=stepCount; i++)
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
  
 }
}
